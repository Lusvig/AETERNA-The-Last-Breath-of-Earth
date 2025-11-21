#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AeternaGameMode.generated.h"

class ASurvivalManager;
class AChoiceTracker;
class AMemoryEchoSystem;

/**
 * FAeternaGameState
 * Main game state structure tracking world conditions, survival metrics, and narrative state
 */
USTRUCT(BlueprintType)
struct FAeternaGameState
{
	GENERATED_BODY()

	// Day counter (1-275, game end at 275)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	int32 CurrentDay;

	// Time of day (0.0 - 24.0)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	float TimeOfDay;

	// Environmental contamination (0.0 - 1.0)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	float RadiationLevel;

	// Tracked choices for legacy system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	float CompassionScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	float EnvironmentalScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	int32 TotalKillCount;
};

/**
 * AAeternaGameMode
 * Main game mode class handling core game systems
 */
UCLASS()
class AETERNA_API AAeternaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAeternaGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Game State")
	FAeternaGameState GetGameState() const { return GameState; }

	UFUNCTION(BlueprintCallable, Category = "Game State")
	int32 GetCurrentDay() const { return GameState.CurrentDay; }

	UFUNCTION(BlueprintCallable, Category = "Game State")
	float GetTimeOfDay() const { return GameState.TimeOfDay; }

	UFUNCTION(BlueprintCallable, Category = "Game State")
	float GetRadiationLevel() const { return GameState.RadiationLevel; }

	// Game flow
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void StartNewGame();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void LoadGame(const FString& SaveName);

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void SaveGame(const FString& SaveName);

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void EndGame(int32 EndingIndex);

	// Choice tracking
	UFUNCTION(BlueprintCallable, Category = "Choices")
	void RecordMoralChoice(bool bWasCompassionate, float Weight = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Choices")
	void RecordEnvironmentalChoice(bool bWasConservative, float Weight = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Choices")
	void RecordKill(AActor* Victim);

	// World state updates
	UFUNCTION(BlueprintCallable, Category = "World State")
	void UpdateRadiationLevel(float NewLevel);

	UFUNCTION(BlueprintCallable, Category = "World State")
	void TriggerRadiationStorm();

	UFUNCTION(BlueprintCallable, Category = "World State")
	void AdvanceDay();

protected:
	// Core game managers
	UPROPERTY()
	ASurvivalManager* SurvivalManager;

	UPROPERTY()
	AChoiceTracker* ChoiceTracker;

	UPROPERTY()
	AMemoryEchoSystem* MemoryEchoSystem;

	// Current game state
	UPROPERTY()
	FAeternaGameState GameState;

	// Game settings
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bIsIronMode;

	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bIsHardcoreMode;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float DifficultyModifier;

private:
	// Internal time tracking
	float TimeAccumulator;
	float DayLength; // 30 minutes real-time = 1 day in-game
};
