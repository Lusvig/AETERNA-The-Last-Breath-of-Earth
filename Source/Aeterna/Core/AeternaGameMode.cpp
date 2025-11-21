#include "AeternaGameMode.h"
#include "../SurvivalSystems/SurvivalManager.h"
#include "../Narrative/ChoiceTracker.h"
#include "../Narrative/MemoryEchoSystem.h"

AAeternaGameMode::AAeternaGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	bIsIronMode = false;
	bIsHardcoreMode = false;
	DifficultyModifier = 1.0f;

	TimeAccumulator = 0.0f;
	DayLength = 30.0f * 60.0f; // 30 minutes = 1 full day
}

void AAeternaGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Initialize game state
	GameState.CurrentDay = 1;
	GameState.TimeOfDay = 6.0f; // 6 AM start
	GameState.RadiationLevel = 0.3f; // 30% baseline radiation
	GameState.CompassionScore = 50.0f; // Start neutral
	GameState.EnvironmentalScore = 0.0f; // Start neutral
	GameState.TotalKillCount = 0;

	// Spawn core managers if not already present
	if (!SurvivalManager)
	{
		SurvivalManager = GetWorld()->SpawnActor<ASurvivalManager>();
	}

	if (!ChoiceTracker)
	{
		ChoiceTracker = GetWorld()->SpawnActor<AChoiceTracker>();
	}

	if (!MemoryEchoSystem)
	{
		MemoryEchoSystem = GetWorld()->SpawnActor<AMemoryEchoSystem>();
	}

	UE_LOG(LogTemp, Warning, TEXT("AETERNA GameMode initialized. Day 1, 6:00 AM. Timekeeper: %f"), DayLength);
}

void AAeternaGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Advance time of day
	TimeAccumulator += DeltaTime;

	float TimeProgression = TimeAccumulator / DayLength;
	GameState.TimeOfDay += (TimeProgression * 24.0f);

	if (GameState.TimeOfDay >= 24.0f)
	{
		GameState.TimeOfDay -= 24.0f;
		AdvanceDay();
	}

	TimeAccumulator = 0.0f;
}

void AAeternaGameMode::StartNewGame()
{
	// Reset game state
	GameState.CurrentDay = 1;
	GameState.TimeOfDay = 6.0f;
	GameState.RadiationLevel = 0.3f;
	GameState.CompassionScore = 50.0f;
	GameState.EnvironmentalScore = 0.0f;
	GameState.TotalKillCount = 0;

	UE_LOG(LogTemp, Warning, TEXT("New game started."));
}

void AAeternaGameMode::LoadGame(const FString& SaveName)
{
	// TODO: Implement save game loading from file
	UE_LOG(LogTemp, Warning, TEXT("Loading game: %s"), *SaveName);
}

void AAeternaGameMode::SaveGame(const FString& SaveName)
{
	// TODO: Implement save game to file
	UE_LOG(LogTemp, Warning, TEXT("Saving game: %s at Day %d"), *SaveName, GameState.CurrentDay);
}

void AAeternaGameMode::EndGame(int32 EndingIndex)
{
	// TODO: Calculate final ending and trigger cinematics
	UE_LOG(LogTemp, Warning, TEXT("Game ending triggered. Ending Index: %d"), EndingIndex);
}

void AAeternaGameMode::RecordMoralChoice(bool bWasCompassionate, float Weight)
{
	if (bWasCompassionate)
	{
		GameState.CompassionScore = FMath::Clamp(GameState.CompassionScore + (10.0f * Weight), 0.0f, 100.0f);
	}
	else
	{
		GameState.CompassionScore = FMath::Clamp(GameState.CompassionScore - (10.0f * Weight), 0.0f, 100.0f);
	}

	if (ChoiceTracker)
	{
		ChoiceTracker->RecordChoice(TEXT("Moral"), bWasCompassionate ? 1.0f : -1.0f, Weight);
	}

	UE_LOG(LogTemp, Warning, TEXT("Moral choice recorded. Compassion now: %.1f"), GameState.CompassionScore);
}

void AAeternaGameMode::RecordEnvironmentalChoice(bool bWasConservative, float Weight)
{
	if (bWasConservative)
	{
		GameState.EnvironmentalScore = FMath::Clamp(GameState.EnvironmentalScore + (10.0f * Weight), -100.0f, 100.0f);
	}
	else
	{
		GameState.EnvironmentalScore = FMath::Clamp(GameState.EnvironmentalScore - (10.0f * Weight), -100.0f, 100.0f);
	}

	if (ChoiceTracker)
	{
		ChoiceTracker->RecordChoice(TEXT("Environmental"), bWasConservative ? 1.0f : -1.0f, Weight);
	}

	UE_LOG(LogTemp, Warning, TEXT("Environmental choice recorded. Score now: %.1f"), GameState.EnvironmentalScore);
}

void AAeternaGameMode::RecordKill(AActor* Victim)
{
	GameState.TotalKillCount++;

	if (ChoiceTracker)
	{
		ChoiceTracker->RecordChoice(TEXT("Kill"), 1.0f, 1.0f);
	}

	UE_LOG(LogTemp, Warning, TEXT("Kill recorded. Total kills: %d"), GameState.TotalKillCount);
}

void AAeternaGameMode::UpdateRadiationLevel(float NewLevel)
{
	GameState.RadiationLevel = FMath::Clamp(NewLevel, 0.0f, 1.0f);
	UE_LOG(LogTemp, Warning, TEXT("Radiation level updated: %.2f"), GameState.RadiationLevel);
}

void AAeternaGameMode::TriggerRadiationStorm()
{
	// Radiation temporarily increases
	float OriginalLevel = GameState.RadiationLevel;
	GameState.RadiationLevel = FMath::Clamp(GameState.RadiationLevel + 0.3f, 0.0f, 1.0f);

	UE_LOG(LogTemp, Warning, TEXT("RADIATION STORM TRIGGERED. Level: %.2f -> %.2f"), OriginalLevel, GameState.RadiationLevel);

	// TODO: Play storm VFX, sound effects, apply radiation damage to exposed players
}

void AAeternaGameMode::AdvanceDay()
{
	GameState.CurrentDay++;

	// Check if player reached end (Day 275 = atmospheric collapse)
	if (GameState.CurrentDay >= 275)
	{
		UE_LOG(LogTemp, Warning, TEXT("FINAL DAY REACHED. Atmosphere collapse imminent."));
		// TODO: Trigger final sequence
	}

	// Periodic events
	if (GameState.CurrentDay % 7 == 0)
	{
		TriggerRadiationStorm();
	}

	UE_LOG(LogTemp, Warning, TEXT("Day advanced to: %d"), GameState.CurrentDay);
}
