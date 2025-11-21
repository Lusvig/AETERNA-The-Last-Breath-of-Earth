#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParisLevel.generated.h"

class ACreatureController;
class AEnvironmentInteraction;

// Paris region zones
UENUM(BlueprintType)
enum class EParisZone : uint8
{
	NotreDAme = 0		UMETA(DisplayName = "Notre-Dame Cathedral"),
	LouvreMuseum = 1	UMETA(DisplayName = "Louvre Museum"),
	MetroTunnels = 2	UMETA(DisplayName = "Metro Tunnels"),
	EiffelTower = 3		UMETA(DisplayName = "Eiffel Tower"),
	SeineFlooded = 4	UMETA(DisplayName = "Flooded Seine"),
	ParkReclaimed = 5	UMETA(DisplayName = "Park (Reclaimed)")
};

// Story progression state
UENUM(BlueprintType)
enum class EParisProgressionState : uint8
{
	Arrival = 0				UMETA(DisplayName = "First Arrival"),
	ExplorationPhase = 1	UMETA(DisplayName = "Exploration"),
	SarahEncounter = 2		UMETA(DisplayName = "Discover Sarah's Echo"),
	DeerHerdMeeting = 3		UMETA(DisplayName = "Meet Bioluminescent Herd"),
	FloodingEvent = 4		UMETA(DisplayName = "Water Level Rising"),
	EscapeSequence = 5		UMETA(DisplayName = "Escape Sequence"),
	Completion = 6			UMETA(DisplayName = "Vertical Slice Complete")
};

/**
 * AParisLevel
 * Main orchestrator for Paris Overgrown vertical slice
 * Coordinates weather, creature spawning, NPC encounters, narrative progression
 */
UCLASS()
class AETERNA_API AParisLevel : public AActor
{
	GENERATED_BODY()

public:
	AParisLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Level progression
	UFUNCTION(BlueprintCallable, Category = "Paris")
	void ProgressStoryState();

	UFUNCTION(BlueprintCallable, Category = "Paris")
	EParisProgressionState GetCurrentState() const { return CurrentState; }

	// Environmental effects
	UFUNCTION(BlueprintCallable, Category = "Environment")
	void TriggerFloodingEvent(float RiseRate = 10.0f);

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void TriggerRadiationStorm(float Intensity = 0.8f);

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void UpdateWaterLevel(float NewLevel);

	// Creature spawning
	UFUNCTION(BlueprintCallable, Category = "Creatures")
	void SpawnBioluminescentHerd(int32 HerdSize = 8);

	UFUNCTION(BlueprintCallable, Category = "Creatures")
	void SpawnScavengingCreatures();

	// Narrative triggers
	UFUNCTION(BlueprintCallable, Category = "Narrative")
	void TriggerSarahEcho();

	UFUNCTION(BlueprintCallable, Category = "Narrative")
	void TriggerHerdEncounter();

	// Zone management
	UFUNCTION(BlueprintCallable, Category = "Paris")
	void ActivateZone(EParisZone Zone);

	UFUNCTION(BlueprintCallable, Category = "Paris")
	void DeactivateZone(EParisZone Zone);

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Paris")
	float GetWaterLevel() const { return CurrentWaterLevel; }

	UFUNCTION(BlueprintCallable, Category = "Paris")
	float GetRadiationIntensity() const { return RadiationIntensity; }

	UFUNCTION(BlueprintCallable, Category = "Environment")
	float GetAmbientTemperature() const { return AmbientTemperature; }

	// Events
	DECLARE_MULTICAST_DELEGATE(FOnFloodingBegins);
	DECLARE_MULTICAST_DELEGATE(FOnHerdEncounter);
	DECLARE_MULTICAST_DELEGATE(FOnSarahEchoTriggered);
	DECLARE_MULTICAST_DELEGATE(FOnLevelCompletion);

	FOnFloodingBegins OnFloodingBegins;
	FOnHerdEncounter OnHerdEncounter;
	FOnSarahEchoTriggered OnSarahEchoTriggered;
	FOnLevelCompletion OnLevelCompletion;

protected:
	// Story state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paris")
	EParisProgressionState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paris")
	float TimeInState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paris")
	float GameDay;

	// Environmental state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float CurrentWaterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float MaxWaterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float RadiationIntensity; // 0-1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float AmbientTemperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	bool bFloodingActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float FloodRiseRate; // Units per second

	// Creatures
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creatures")
	TArray<ACreatureController*> ActiveCreatures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creatures")
	int32 MaxCreatureCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creatures")
	bool bHerdSpawned;

	// Interactions/Collectibles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactions")
	TArray<AEnvironmentInteraction*> InteractionPoints;

	// Zone states
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zones")
	TMap<EParisZone, bool> ZoneActiveMap;

	// Audio/ambience
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float AmbientAudioIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	bool bPlayRadiationHum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	bool bPlayFloodingSounds;

private:
	void InitializeZones();
	void UpdateEnvironmentEffects(float DeltaTime);
	void UpdateProgressionState(float DeltaTime);
	void SpawnInitialCreatures();
	void UpdateRadiationLevels();
};
