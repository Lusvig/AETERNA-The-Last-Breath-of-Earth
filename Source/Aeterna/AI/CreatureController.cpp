#include "CreatureController.h"
#include "GameFramework/Character.h"

ACreatureController::ACreatureController()
{
	PrimaryActorTick.bCanEverTick = true;

	CreatureType = ECreatureType::BioluminescentDeer;
	CurrentBehavior = ECreatureBehavior::Idle;
	PreviousBehavior = ECreatureBehavior::Idle;

	Health = 100.0f;
	MaxHealth = 100.0f;
	AggressionLevel = 0.0f;
	FearLevel = 0.0f;

	bBioluminesceActive = true;
	BioluminesenceIntensity = 0.7f;
	BioluminesenceColor = FLinearColor(0.0f, 1.0f, 0.6f, 1.0f); // Cyan-green
	PulseFrequency = 1.0f;

	RadiationTolerance = 0.8f; // High tolerance for evolved creatures
	CurrentRadiationExposure = 0.0f;

	HerdLeader = nullptr;
	HerdCohesionRange = 500.0f;

	BehaviorChangeTimer = 0.0f;
	NextBehaviorChangeTime = FMath::RandRange(10.0f, 30.0f);
}

void ACreatureController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("CreatureController initialized: %s (Type: %d)"), 
		   *GetName(), (int32)CreatureType);

	// Set initial behavior
	SetBehavior(ECreatureBehavior::Grazing);
}

void ACreatureController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateBehavior(DeltaTime);
	ProcessRadiationEffects(DeltaTime);
	UpdateBioluminescence(DeltaTime);
	CheckForHerdCohesion();
}

void ACreatureController::SetBehavior(ECreatureBehavior NewBehavior)
{
	if (NewBehavior == CurrentBehavior)
	{
		return;
	}

	PreviousBehavior = CurrentBehavior;
	CurrentBehavior = NewBehavior;

	switch (CurrentBehavior)
	{
	case ECreatureBehavior::Idle:
		UE_LOG(LogTemp, Warning, TEXT("%s: Idle"), *GetName());
		break;
	case ECreatureBehavior::Grazing:
		UE_LOG(LogTemp, Warning, TEXT("%s: Grazing"), *GetName());
		AggressionLevel = 0.0f;
		break;
	case ECreatureBehavior::Fleeing:
		UE_LOG(LogTemp, Error, TEXT("%s: FLEEING"), *GetName());
		FearLevel = 100.0f;
		break;
	case ECreatureBehavior::Hunting:
		UE_LOG(LogTemp, Error, TEXT("%s: HUNTING"), *GetName());
		AggressionLevel = 80.0f;
		break;
	case ECreatureBehavior::Sleeping:
		UE_LOG(LogTemp, Warning, TEXT("%s: Sleeping"), *GetName());
		DeactivateBioluminescence();
		break;
	case ECreatureBehavior::Bioluminescing:
		ActivateBioluminescence();
		break;
	default:
		break;
	}
}

void ACreatureController::FleeFromThreat(FVector ThreatLocation)
{
	SetBehavior(ECreatureBehavior::Fleeing);
	FearLevel = 100.0f;

	// Calculate flee direction (away from threat)
	if (GetPawn())
	{
		FVector FleeDirection = (GetPawn()->GetActorLocation() - ThreatLocation).GetSafeNormal();
		// TODO: Make creature move in flee direction
	}
}

void ACreatureController::HuntPrey(AActor* Prey)
{
	if (!Prey)
	{
		return;
	}

	SetBehavior(ECreatureBehavior::Hunting);
	AggressionLevel = 80.0f;

	// TODO: Chase prey with line-of-sight
	UE_LOG(LogTemp, Warning, TEXT("%s hunting %s"), *GetName(), *Prey->GetName());
}

void ACreatureController::GrazeAtLocation(FVector GrazeLocation)
{
	SetBehavior(ECreatureBehavior::Grazing);

	// TODO: Move to grazing location and idle
	UE_LOG(LogTemp, Warning, TEXT("%s grazing at location"), *GetName());
}

void ACreatureController::ActivateBioluminescence()
{
	bBioluminesceActive = true;
	BioluminesenceIntensity = 1.0f;

	UE_LOG(LogTemp, Warning, TEXT("%s: Bioluminescence ACTIVE"), *GetName());
}

void ACreatureController::DeactivateBioluminescence()
{
	bBioluminesceActive = false;
	BioluminesenceIntensity = 0.0f;

	UE_LOG(LogTemp, Warning, TEXT("%s: Bioluminescence OFF"), *GetName());
}

void ACreatureController::PulseBioluminescence(float NewPulseFrequency)
{
	bBioluminesceActive = true;
	PulseFrequency = NewPulseFrequency;

	UE_LOG(LogTemp, Warning, TEXT("%s: Pulsing at %.1f Hz"), *GetName(), PulseFrequency);
}

void ACreatureController::ExposeToRadiation(float RadiationLevel)
{
	CurrentRadiationExposure += RadiationLevel;

	// At high radiation, creatures become more bioluminescent (defensive response)
	if (CurrentRadiationExposure > 50.0f)
	{
		BioluminesenceIntensity = FMath::Min(BioluminesenceIntensity + 0.1f, 1.0f);
		PulseFrequency = 2.0f; // Panic pulse

		// Take damage if exposure too high
		if (CurrentRadiationExposure > RadiationTolerance * 100.0f)
		{
			Health -= 5.0f;
		}
	}
}

void ACreatureController::ReactToSound(FVector SoundLocation, float SoundVolume)
{
	// If sound is loud and nearby, creature reacts
	if (SoundVolume > 0.7f)
	{
		FleeFromThreat(SoundLocation);
	}
	else if (SoundVolume > 0.4f && CurrentBehavior == ECreatureBehavior::Grazing)
	{
		// Alert state
		FearLevel = 40.0f;
		BioluminesenceIntensity = 0.9f; // Brighten to see better
	}
}

void ACreatureController::SetHerdLeader(ACharacter* Leader)
{
	HerdLeader = Leader;

	if (HerdLeader)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s joined herd led by %s"), *GetName(), *HerdLeader->GetName());
	}
}

void ACreatureController::FollowHerd()
{
	if (HerdLeader)
	{
		// TODO: Move toward herd leader
		SetBehavior(ECreatureBehavior::Migrating);
	}
}

void ACreatureController::UpdateBehavior(float DeltaTime)
{
	BehaviorChangeTimer += DeltaTime;

	// Periodically change behavior naturally
	if (BehaviorChangeTimer >= NextBehaviorChangeTime)
	{
		BehaviorChangeTimer = 0.0f;
		NextBehaviorChangeTime = FMath::RandRange(15.0f, 45.0f);

		// Random behavior switches (when not threatened)
		if (CurrentBehavior == ECreatureBehavior::Grazing)
		{
			int32 Rand = FMath::RandRange(0, 3);
			if (Rand == 0)
			{
				SetBehavior(ECreatureBehavior::Sleeping);
			}
			else if (Rand == 1)
			{
				SetBehavior(ECreatureBehavior::Idle);
			}
		}
		else if (CurrentBehavior == ECreatureBehavior::Idle)
		{
			SetBehavior(ECreatureBehavior::Grazing);
		}
	}
}

void ACreatureController::ProcessRadiationEffects(float DeltaTime)
{
	// Radiation slowly drains
	CurrentRadiationExposure = FMath::Max(0.0f, CurrentRadiationExposure - (1.0f * DeltaTime));

	// Mutations may occur at extreme radiation
	if (CurrentRadiationExposure > 80.0f)
	{
		// Creature becomes more aggressive
		AggressionLevel += 0.5f * DeltaTime;
	}
}

void ACreatureController::UpdateBioluminescence(float DeltaTime)
{
	if (!bBioluminesceActive)
	{
		BioluminesenceIntensity = 0.0f;
		return;
	}

	// Pulse effect
	if (PulseFrequency > 0.0f)
	{
		float PulseValue = FMath::Sin(GetWorld()->GetTimeSeconds() * PulseFrequency * 2.0f * PI);
		BioluminesenceIntensity = (PulseValue + 1.0f) / 2.0f; // Oscillate 0-1
	}

	// Respond to player proximity (dim when hiding)
	if (GetPawn())
	{
		if (FearLevel > 50.0f)
		{
			// Dim bioluminescence when scared
			BioluminesenceIntensity *= 0.5f;
		}
	}
}

void ACreatureController::CheckForHerdCohesion()
{
	// Find nearby creatures to form/maintain herd
	if (GetPawn())
	{
		// TODO: Raycasts to find other creatures
		// Adjust behavior based on herd proximity
	}
}
