#include "ParisLevel.h"
#include "../AI/CreatureController.h"
#include "EnvironmentInteraction.h"
#include "Kismet/GameplayStatics.h"

AParisLevel::AParisLevel()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	CurrentState = EParisProgressionState::Arrival;
	TimeInState = 0.0f;
	GameDay = 47.0f; // Day 47 of countdown

	CurrentWaterLevel = 0.0f;
	MaxWaterLevel = 800.0f; // Units (represents 8-meter rise in Seine)
	RadiationIntensity = 0.15f; // Low radiation in Paris proper
	AmbientTemperature = 12.0f; // Cool spring day before everything

	bFloodingActive = false;
	FloodRiseRate = 0.0f;

	MaxCreatureCount = 12;
	bHerdSpawned = false;

	AmbientAudioIntensity = 0.6f;
	bPlayRadiationHum = false;
	bPlayFloodingSounds = false;
}

void AParisLevel::BeginPlay()
{
	Super::BeginPlay();

	InitializeZones();
	SpawnInitialCreatures();

	UE_LOG(LogTemp, Warning, TEXT("Paris Overgrown (Day 47) initialized"));
	UE_LOG(LogTemp, Warning, TEXT("Water Level: %.1f/%1f units"), CurrentWaterLevel, MaxWaterLevel);
	UE_LOG(LogTemp, Warning, TEXT("Radiation: %.2f"), RadiationIntensity);
	UE_LOG(LogTemp, Warning, TEXT("Temperature: %.1f°C"), AmbientTemperature);
}

void AParisLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeInState += DeltaTime;

	UpdateEnvironmentEffects(DeltaTime);
	UpdateProgressionState(DeltaTime);
	UpdateRadiationLevels();
}

void AParisLevel::ProgressStoryState()
{
	EParisProgressionState PreviousState = CurrentState;

	switch (CurrentState)
	{
	case EParisProgressionState::Arrival:
		CurrentState = EParisProgressionState::ExplorationPhase;
		UE_LOG(LogTemp, Warning, TEXT("PARIS: Entered Exploration Phase"));
		break;

	case EParisProgressionState::ExplorationPhase:
		// Trigger once player reaches Notre-Dame interior
		CurrentState = EParisProgressionState::SarahEncounter;
		TriggerSarahEcho();
		UE_LOG(LogTemp, Error, TEXT("PARIS: Sarah's Echo triggered"));
		break;

	case EParisProgressionState::SarahEncounter:
		CurrentState = EParisProgressionState::DeerHerdMeeting;
		TriggerHerdEncounter();
		UE_LOG(LogTemp, Warning, TEXT("PARIS: Herd encounter triggered"));
		break;

	case EParisProgressionState::DeerHerdMeeting:
		// After 15 minutes of herd interaction
		CurrentState = EParisProgressionState::FloodingEvent;
		TriggerFloodingEvent(15.0f); // Gradual water rise
		OnFloodingBegins.Broadcast();
		UE_LOG(LogTemp, Error, TEXT("PARIS: FLOODING EVENT BEGINS - Water rising at 15 units/sec"));
		break;

	case EParisProgressionState::FloodingEvent:
		CurrentState = EParisProgressionState::EscapeSequence;
		UE_LOG(LogTemp, Error, TEXT("PARIS: ESCAPE SEQUENCE - MUST REACH HIGH GROUND"));
		break;

	case EParisProgressionState::EscapeSequence:
		CurrentState = EParisProgressionState::Completion;
		OnLevelCompletion.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("PARIS: Vertical Slice COMPLETE"));
		break;

	default:
		break;
	}

	TimeInState = 0.0f;
}

void AParisLevel::TriggerFloodingEvent(float RiseRate)
{
	bFloodingActive = true;
	FloodRiseRate = RiseRate;
	bPlayFloodingSounds = true;

	UE_LOG(LogTemp, Error, TEXT("FLOODING: Water rising at %.1f units/sec"), RiseRate);
	UE_LOG(LogTemp, Error, TEXT("FLOODING: Estimated time to max level: %.1f seconds"), MaxWaterLevel / RiseRate);
}

void AParisLevel::TriggerRadiationStorm(float Intensity)
{
	RadiationIntensity = FMath::Min(RadiationIntensity + Intensity, 1.0f);
	bPlayRadiationHum = true;

	UE_LOG(LogTemp, Error, TEXT("RADIATION STORM: Intensity %.2f"), RadiationIntensity);
}

void AParisLevel::UpdateWaterLevel(float NewLevel)
{
	CurrentWaterLevel = FMath::Clamp(NewLevel, 0.0f, MaxWaterLevel);

	// Water level affects multiple systems
	// - Zone accessibility (lower zones become impassable)
	// - Creature behavior (herd flees to higher ground)
	// - Environmental hazards (cold water exposure, drowning risk)

	if (CurrentWaterLevel > MaxWaterLevel * 0.5f)
	{
		// More than halfway flooded - CRITICAL state
		bPlayFloodingSounds = true;
	}
}

void AParisLevel::SpawnBioluminescentHerd(int32 HerdSize)
{
	if (bHerdSpawned)
	{
		return;
	}

	bHerdSpawned = true;

	for (int32 i = 0; i < HerdSize && ActiveCreatures.Num() < MaxCreatureCount; ++i)
	{
		// Spawn at various locations around Louvre/Seine
		FVector SpawnLocation = GetActorLocation() + FVector(
			FMath::RandRange(-500.0f, 500.0f),
			FMath::RandRange(-500.0f, 500.0f),
			50.0f
		);

		ACreatureController* CreatureController = GetWorld()->SpawnActor<ACreatureController>(SpawnLocation, FRotator::ZeroRotator);
		if (CreatureController)
		{
			CreatureController->SetCreatureType(ECreatureType::BioluminescentDeer);
			if (i == 0)
			{
				CreatureController->SetBehavior(ECreatureBehavior::Grazing);
				// Other deer will follow
			}
			else
			{
				CreatureController->SetHerdLeader(nullptr); // Will be set by first creature
			}

			ActiveCreatures.Add(CreatureController);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("HERD: %d bioluminescent deer spawned"), ActiveCreatures.Num());
}

void AParisLevel::SpawnScavengingCreatures()
{
	// Mutated creatures that scavenge in ruins
	// Less friendly than deer
}

void AParisLevel::TriggerSarahEcho()
{
	OnSarahEchoTriggered.Broadcast();

	// Echo ID 1 = Sarah's Last Day
	// TODO: Call MemoryEchoCinematic->PlayMemoryEcho(1)
	UE_LOG(LogTemp, Warning, TEXT("NARRATIVE: Sarah's Memory Echo triggered"));
}

void AParisLevel::TriggerHerdEncounter()
{
	SpawnBioluminescentHerd(8);
	OnHerdEncounter.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("CREATURES: Herd encounter activated"));
}

void AParisLevel::ActivateZone(EParisZone Zone)
{
	ZoneActiveMap.FindOrAdd(Zone) = true;

	switch (Zone)
	{
	case EParisZone::NotreDAme:
		UE_LOG(LogTemp, Warning, TEXT("ZONE: Notre-Dame activated"));
		break;
	case EParisZone::LouvreMuseum:
		UE_LOG(LogTemp, Warning, TEXT("ZONE: Louvre activated"));
		break;
	case EParisZone::MetroTunnels:
		UE_LOG(LogTemp, Warning, TEXT("ZONE: Metro Tunnels activated"));
		break;
	case EParisZone::EiffelTower:
		UE_LOG(LogTemp, Warning, TEXT("ZONE: Eiffel Tower activated"));
		break;
	case EParisZone::SeineFlooded:
		UE_LOG(LogTemp, Warning, TEXT("ZONE: Flooded Seine activated"));
		break;
	case EParisZone::ParkReclaimed:
		UE_LOG(LogTemp, Warning, TEXT("ZONE: Reclaimed Park activated"));
		break;
	}
}

void AParisLevel::DeactivateZone(EParisZone Zone)
{
	ZoneActiveMap.FindOrAdd(Zone) = false;
}

void AParisLevel::InitializeZones()
{
	// Start with just Notre-Dame and surroundings accessible
	ActivateZone(EParisZone::NotreDAme);
	ActivateZone(EParisZone::SeineFlooded);
	ActivateZone(EParisZone::ParkReclaimed);

	UE_LOG(LogTemp, Warning, TEXT("ZONES: Initialized - Notre-Dame, Seine, Park accessible"));
}

void AParisLevel::UpdateEnvironmentEffects(float DeltaTime)
{
	// Apply flooding
	if (bFloodingActive)
	{
		UpdateWaterLevel(CurrentWaterLevel + (FloodRiseRate * DeltaTime));

		if (CurrentWaterLevel >= MaxWaterLevel)
		{
			bFloodingActive = false;
			UE_LOG(LogTemp, Error, TEXT("FLOODING: MAXIMUM LEVEL REACHED - Level completely submerged"));
		}
	}

	// Temperature variations
	float TimeOfDay = FMath::Fmod(GetWorld()->GetTimeSeconds() / 60.0f, 24.0f); // Simulate 24-hour cycle
	float TemperatureVariation = FMath::Sin(TimeOfDay * PI / 12.0f) * 8.0f; // ±8°C variation
	AmbientTemperature = 12.0f + TemperatureVariation;

	// Radiation increases slightly during storm
	if (bPlayRadiationHum)
	{
		RadiationIntensity = FMath::Max(RadiationIntensity - (0.01f * DeltaTime), 0.1f); // Gradually decrease
	}
}

void AParisLevel::UpdateProgressionState(float DeltaTime)
{
	// Auto-progress story if conditions met
	switch (CurrentState)
	{
	case EParisProgressionState::Arrival:
		// Progress after 2 minutes of exploration
		if (TimeInState > 120.0f)
		{
			ProgressStoryState();
		}
		break;

	case EParisProgressionState::ExplorationPhase:
		// Progress when player reaches Notre-Dame interior
		// TODO: Check player location
		if (TimeInState > 180.0f)
		{
			ProgressStoryState();
		}
		break;

	case EParisProgressionState::DeerHerdMeeting:
		// Progress after 15 minutes with herd
		if (TimeInState > 900.0f)
		{
			ProgressStoryState();
		}
		break;

	case EParisProgressionState::FloodingEvent:
		// Progress when water reaches critical level or player escapes
		if (CurrentWaterLevel >= MaxWaterLevel * 0.8f)
		{
			ProgressStoryState();
		}
		break;

	default:
		break;
	}
}

void AParisLevel::SpawnInitialCreatures()
{
	// Spawn ambient creatures throughout level
	// Not hostile, just environmental flavor

	// TODO: Spawn various small creatures in trees/ruins
}

void AParisLevel::UpdateRadiationLevels()
{
	// Radiation varies by zone
	// Near Metro/underground: higher
	// In open air: lower

	// TODO: Check player location and adjust radiation accordingly
}
