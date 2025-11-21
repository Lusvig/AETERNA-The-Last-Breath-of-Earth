#include "PsychologicalSystem.h"

UPsychologicalSystem::UPsychologicalSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.2f;

	SanityLevel = 50.0f; // Start neutral
	CurrentState = EPsychologicalState::Stable;
	TraumaLevel = 0.0f;

	AccumulatedDeathWitnesses = 0.0f;
	IsolationTime = 0.0f;
	LastSocialInteractionTime = -FLT_MAX;

	bIsHallucinating = false;
	HallucinationIntensity = 0.0f;
	LastHallucinationSource = ETraumaType::Witnessed_Death;

	ParanoiaLevel = 0.0f;
	DespairLevel = 0.0f;

	BreakdownCount = 0;
	TimeSinceLastBreakdown = 0.0f;
	bSuicidalThoughtsActive = false;

	HallucinationDescription = TEXT("");
	HallucinationDuration = 0.0f;
	HallucinationTimer = 0.0f;

	bHeartbeatAudioPlaying = false;
	bDistortedAudio = false;
	bScreenDistortion = false;
	ScreenDistortionIntensity = 0.0f;
}

void UPsychologicalSystem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PsychologicalSystem initialized on %s"), *GetOwnerName());
}

void UPsychologicalSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateIsolationTrauma(DeltaTime);
	ApplyHallucinationEffects(DeltaTime);
	UpdatePsychologicalState(DeltaTime);
	CheckForBreakdown();
	CheckSuicideRisk();
}

void UPsychologicalSystem::InflictTrauma(ETraumaType TraumaType, float Severity)
{
	float TraumaDamage = 0.0f;

	switch (TraumaType)
	{
	case ETraumaType::Witnessed_Death:
		TraumaDamage = 15.0f * Severity;
		AccumulatedDeathWitnesses += 1.0f;
		UE_LOG(LogTemp, Error, TEXT("TRAUMA: Witnessed death #%.0f"), AccumulatedDeathWitnesses);
		break;

	case ETraumaType::Mass_Grave:
		TraumaDamage = 40.0f * Severity; // SEVERE
		UE_LOG(LogTemp, Error, TEXT("TRAUMA: Found mass grave - SEVERE PSYCHOLOGICAL DAMAGE"));
		break;

	case ETraumaType::Starvation:
		TraumaDamage = 10.0f * Severity;
		UE_LOG(LogTemp, Error, TEXT("TRAUMA: Starvation stress"));
		break;

	case ETraumaType::Drowning:
		TraumaDamage = 25.0f * Severity; // Near-death experience
		UE_LOG(LogTemp, Error, TEXT("TRAUMA: Near-drowning PTSD"));
		break;

	case ETraumaType::Radiation:
		TraumaDamage = 15.0f * Severity;
		bDistortedAudio = true; // Auditory hallucinations from radiation
		UE_LOG(LogTemp, Error, TEXT("TRAUMA: Radiation exposure"));
		break;

	case ETraumaType::Isolation:
		// Handled separately in InflictIsolationTrauma
		break;

	case ETraumaType::Loss:
		TraumaDamage = 35.0f * Severity; // Loss of companion is DEVASTATING
		UE_LOG(LogTemp, Error, TEXT("TRAUMA: Lost companion - SEVERE"));
		break;

	case ETraumaType::Cannibalism:
		TraumaDamage = 50.0f * Severity; // Moral horror of cannibalism
		SanityLevel = FMath::Max(0.0f, SanityLevel - 50.0f);
		UE_LOG(LogTemp, Error, TEXT("TRAUMA: CANNIBALISM - Sanity shattered"));
		break;

	default:
		break;
	}

	TraumaLevel = FMath::Min(TraumaLevel + TraumaDamage, 100.0f);
	SanityLevel = FMath::Max(0.0f, SanityLevel - TraumaDamage);

	TraumaHistory.FindOrAdd(TraumaType) += TraumaDamage;

	// Chance to trigger hallucination immediately
	if (FMath::Rand() % 100 < (TraumaDamage * 0.5f))
	{
		TriggerHallucination();
	}
}

void UPsychologicalSystem::InflictIsolationTrauma(float TimeAloneSeconds)
{
	// Extreme isolation creates psychological damage
	// After 48 hours alone: sanity -1/min
	// After 72 hours: severe breakdown risk

	float IsolationMultiplier = 1.0f;
	if (TimeAloneSeconds > 172800.0f) // 48 hours
	{
		IsolationMultiplier = 2.0f;
		UE_LOG(LogTemp, Error, TEXT("ISOLATION: 48+ hours alone - severe sanity damage"));
	}

	float IsolationDamage = (TimeAloneSeconds / 3600.0f) * IsolationMultiplier;
	TraumaLevel = FMath::Min(TraumaLevel + IsolationDamage, 100.0f);
	SanityLevel = FMath::Max(0.0f, SanityLevel - IsolationDamage);

	if (SanityLevel < 30.0f)
	{
		bSuicidalThoughtsActive = true;
	}
}

void UPsychologicalSystem::WitnessDeath(AActor* DeadNPC)
{
	InflictTrauma(ETraumaType::Witnessed_Death, 1.5f);

	if (DeadNPC)
	{
		UE_LOG(LogTemp, Error, TEXT("WITNESSED DEATH: %s"), *DeadNPC->GetName());
	}
}

void UPsychologicalSystem::FindMassGrave(int32 BodyCount)
{
	float Severity = FMath::Min((float)BodyCount / 10.0f, 3.0f); // Scale with body count
	InflictTrauma(ETraumaType::Mass_Grave, Severity);

	UE_LOG(LogTemp, Error, TEXT("MASS GRAVE: Found %d bodies - player psychologically destroyed"), BodyCount);
}

void UPsychologicalSystem::TriggerHallucination()
{
	bIsHallucinating = true;
	HallucinationIntensity = FMath::Min(1.0f, TraumaLevel / 100.0f);
	HallucinationDuration = FMath::RandRange(5.0f, 15.0f);
	HallucinationTimer = 0.0f;
	bScreenDistortion = true;
	ScreenDistortionIntensity = HallucinationIntensity;

	// Determine hallucination type
	int32 HallucinationType = FMath::RandRange(0, 3);
	switch (HallucinationType)
	{
	case 0:
		HallucinationDescription = TEXT("Vision of dead loved one");
		bHeartbeatAudioPlaying = true;
		break;
	case 1:
		HallucinationDescription = TEXT("Walls closing in");
		bScreenDistortion = true;
		break;
	case 2:
		HallucinationDescription = TEXT("Everything is red");
		ScreenDistortionIntensity = 1.0f;
		break;
	case 3:
		HallucinationDescription = TEXT("Whispers and screams");
		bDistortedAudio = true;
		break;
	}

	OnHallucination.Broadcast(LastHallucinationSource);

	UE_LOG(LogTemp, Error, TEXT("HALLUCINATION TRIGGERED: %s (Duration: %.1f seconds)"), 
		   *HallucinationDescription, HallucinationDuration);
}

void UPsychologicalSystem::TriggerParanoia()
{
	ParanoiaLevel = FMath::Min(ParanoiaLevel + 30.0f, 100.0f);

	UE_LOG(LogTemp, Error, TEXT("PARANOIA: Player is now extremely suspicious of NPCs and environment"));

	// At high paranoia, NPCs appear hostile
	// Shadows look like threats
	// Sounds are interpreted as danger
}

void UPsychologicalSystem::TriggerDespair()
{
	DespairLevel = FMath::Min(DespairLevel + 40.0f, 100.0f);
	SanityLevel = FMath::Max(0.0f, SanityLevel - 20.0f);

	UE_LOG(LogTemp, Error, TEXT("DESPAIR: All hope lost - why continue? Movement speed reduced"));

	// At max despair, player considers suicide
	if (DespairLevel >= 100.0f)
	{
		bSuicidalThoughtsActive = true;
		OnSuicideThought.Broadcast();
	}
}

void UPsychologicalSystem::FindComfort(const FString& ComfortSource)
{
	// Finding beauty, safety, or connection reduces trauma

	SanityLevel = FMath::Min(SanityLevel + 15.0f, 100.0f);
	TraumaLevel = FMath::Max(0.0f, TraumaLevel - 10.0f);
	ParanoiaLevel = FMath::Max(0.0f, ParanoiaLevel - 20.0f);
	DespairLevel = FMath::Max(0.0f, DespairLevel - 15.0f);

	UE_LOG(LogTemp, Warning, TEXT("COMFORT FOUND: %s - sanity restored slightly"), *ComfortSource);
}

void UPsychologicalSystem::ExperienceBeauty()
{
	// Witnessing beauty (bioluminescent deer, sunset, architecture) helps
	SanityLevel = FMath::Min(SanityLevel + 25.0f, 100.0f);
	TraumaLevel = FMath::Max(0.0f, TraumaLevel - 15.0f);

	// Temporarily stop hallucinations
	bIsHallucinating = false;
	HallucinationTimer = 0.0f;

	UE_LOG(LogTemp, Warning, TEXT("BEAUTY: Witness to wonder - temporary respite from horror"));
}

void UPsychologicalSystem::SocialInteraction()
{
	// Talking to NPCs is one of the strongest sanity restores

	SanityLevel = FMath::Min(SanityLevel + 20.0f, 100.0f);
	IsolationTime = 0.0f;
	LastSocialInteractionTime = GetWorld()->GetTimeSeconds();
	ParanoiaLevel = FMath::Max(0.0f, ParanoiaLevel - 10.0f);

	UE_LOG(LogTemp, Warning, TEXT("SOCIAL: Connection to another human - sanity +20"));
}

void UPsychologicalSystem::UpdatePsychologicalState(float DeltaTime)
{
	// Determine psychological state based on sanity and trauma
	EPsychologicalState NewState = EPsychologicalState::Stable;

	if (SanityLevel > 75.0f && TraumaLevel < 25.0f)
	{
		NewState = EPsychologicalState::Stable;
	}
	else if (SanityLevel > 50.0f && TraumaLevel < 50.0f)
	{
		NewState = EPsychologicalState::Anxious;
	}
	else if (SanityLevel > 30.0f && ParanoiaLevel > 50.0f)
	{
		NewState = EPsychologicalState::Paranoid;
	}
	else if (SanityLevel > 20.0f && DespairLevel > 60.0f)
	{
		NewState = EPsychologicalState::Desperate;
	}
	else if (SanityLevel > 10.0f && bIsHallucinating)
	{
		NewState = EPsychologicalState::Hallucinating;
	}
	else if (SanityLevel <= 10.0f)
	{
		NewState = EPsychologicalState::Broken;
		OnBreakdown.Broadcast();
	}

	if (NewState != CurrentState)
	{
		CurrentState = NewState;
		OnStateChanged.Broadcast(NewState);

		UE_LOG(LogTemp, Error, TEXT("PSYCHOLOGICAL STATE: %d"), (int32)NewState);
	}
}

void UPsychologicalSystem::CheckForBreakdown()
{
	// Repeated trauma can cause mental breakdown
	// Player loses movement control, screams, falls into fetal position

	if (CurrentState == EPsychologicalState::Broken)
	{
		TimeSinceLastBreakdown = 0.0f;
		BreakdownCount++;

		UE_LOG(LogTemp, Error, TEXT("BREAKDOWN #%d: Player mentally broken - seeking shelter"), BreakdownCount);

		// TODO: Apply movement disable
		// TODO: Play anguished audio
		// TODO: Screen goes black/distorted
	}
	else
	{
		TimeSinceLastBreakdown += GetWorld()->DeltaTimeSeconds;
	}
}

void UPsychologicalSystem::ApplyHallucinationEffects(float DeltaTime)
{
	if (!bIsHallucinating)
	{
		return;
	}

	HallucinationTimer += DeltaTime;

	if (HallucinationTimer >= HallucinationDuration)
	{
		bIsHallucinating = false;
		HallucinationIntensity = 0.0f;
		bScreenDistortion = false;
		ScreenDistortionIntensity = 0.0f;

		UE_LOG(LogTemp, Warning, TEXT("Hallucination faded"));
		return;
	}

	// Oscillate hallucination intensity
	float Progress = HallucinationTimer / HallucinationDuration;
	HallucinationIntensity = FMath::Sin(Progress * PI) * (TraumaLevel / 100.0f);
	ScreenDistortionIntensity = HallucinationIntensity;
}

void UPsychologicalSystem::UpdateIsolationTrauma(float DeltaTime)
{
	float TimeSinceSocialContact = GetWorld()->GetTimeSeconds() - LastSocialInteractionTime;

	// Progressive isolation damage
	if (TimeSinceSocialContact > 3600.0f) // 1 hour alone
	{
		IsolationTime += DeltaTime;
		SanityLevel = FMath::Max(0.0f, SanityLevel - (0.01f * DeltaTime));
	}

	// After 48+ hours, escalated damage
	if (IsolationTime > 172800.0f)
	{
		SanityLevel = FMath::Max(0.0f, SanityLevel - (0.1f * DeltaTime));
		ParanoiaLevel = FMath::Min(ParanoiaLevel + (0.05f * DeltaTime), 100.0f);
	}
}

void UPsychologicalSystem::CheckSuicideRisk()
{
	// At SanityLevel 0, player chooses suicide
	// At SanityLevel <10 + extreme isolation/despair, suicidal thoughts escalate

	if (SanityLevel <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("SUICIDE: Player has lost will to live - game over"));

		// TODO: Trigger suicide cinematic
		// Player walks toward dangerous area
		// Game ends
	}

	if (bSuicidalThoughtsActive && (DespairLevel > 80.0f || IsolationTime > 259200.0f)) // 72 hours
	{
		// Escalate suicidal ideation
		OnSuicideThought.Broadcast();
		UE_LOG(LogTemp, Error, TEXT("SUICIDAL IDEATION: Player contemplates death as escape"));
	}
}
