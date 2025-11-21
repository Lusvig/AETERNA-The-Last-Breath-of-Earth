#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CreatureController.generated.h"

// Creature types in AETERNA
UENUM(BlueprintType)
enum class ECreatureType : uint8
{
	BioluminescentDeer = 0		UMETA(DisplayName = "Bioluminescent Deer"),
	MutatedWolf = 1			UMETA(DisplayName = "Mutated Wolf"),
	RadiationBeetle = 2			UMETA(DisplayName = "Radiation Beetle"),
	PhosphorescenceJellyfish = 3	UMETA(DisplayName = "Jellyfish"),
	UnknownPredator = 4			UMETA(DisplayName = "Unknown Predator")
};

// Creature behavior state
UENUM(BlueprintType)
enum class ECreatureBehavior : uint8
{
	Idle = 0				UMETA(DisplayName = "Idle"),
	Grazing = 1				UMETA(DisplayName = "Grazing"),
	Fleeing = 2				UMETA(DisplayName = "Fleeing"),
	Hunting = 3				UMETA(DisplayName = "Hunting"),
	Sleeping = 4			UMETA(DisplayName = "Sleeping"),
	Migrating = 5			UMETA(DisplayName = "Migrating"),
	Bioluminescing = 6		UMETA(DisplayName = "Active Bioluminescence")
};

/**
 * ACreatureController
 * Controls behavior of evolved/mutated creatures
 */
UCLASS()
class AETERNA_API ACreatureController : public AAIController
{
	GENERATED_BODY()

public:
	ACreatureController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Creature properties
	UFUNCTION(BlueprintCallable, Category = "Creature")
	ECreatureType GetCreatureType() const { return CreatureType; }

	UFUNCTION(BlueprintCallable, Category = "Creature")
	ECreatureBehavior GetCurrentBehavior() const { return CurrentBehavior; }

	UFUNCTION(BlueprintCallable, Category = "Creature")
	float GetBioluminesenceIntensity() const { return BioluminesenceIntensity; }

	// Behavior triggers
	UFUNCTION(BlueprintCallable, Category = "Creature")
	void SetBehavior(ECreatureBehavior NewBehavior);

	UFUNCTION(BlueprintCallable, Category = "Creature")
	void FleeFromThreat(FVector ThreatLocation);

	UFUNCTION(BlueprintCallable, Category = "Creature")
	void HuntPrey(AActor* Prey);

	UFUNCTION(BlueprintCallable, Category = "Creature")
	void GrazeAtLocation(FVector GrazeLocation);

	// Bioluminescence effects
	UFUNCTION(BlueprintCallable, Category = "Luminescence")
	void ActivateBioluminescence();

	UFUNCTION(BlueprintCallable, Category = "Luminescence")
	void DeactivateBioluminescence();

	UFUNCTION(BlueprintCallable, Category = "Luminescence")
	void PulseBioluminescence(float PulseFrequency = 1.0f);

	// Environmental reactions
	UFUNCTION(BlueprintCallable, Category = "Environment")
	void ExposeToRadiation(float RadiationLevel);

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void ReactToSound(FVector SoundLocation, float SoundVolume);

	// Herd mechanics
	UFUNCTION(BlueprintCallable, Category = "Herd")
	void SetHerdLeader(ACharacter* Leader);

	UFUNCTION(BlueprintCallable, Category = "Herd")
	void FollowHerd();

protected:
	// Creature properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature")
	ECreatureType CreatureType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature")
	ECreatureBehavior CurrentBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature")
	ECreatureBehavior PreviousBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature")
	float AggressionLevel; // 0-100

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creature")
	float FearLevel; // 0-100

	// Bioluminescence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Luminescence")
	bool bBioluminesceActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Luminescence")
	float BioluminesenceIntensity; // 0-1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Luminescence")
	FLinearColor BioluminesenceColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Luminescence")
	float PulseFrequency; // Hz

	// Radiation adaptation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptation")
	float RadiationTolerance; // 0-1 (how much radiation this creature can handle)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptation")
	float CurrentRadiationExposure;

	// Herd behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Herd")
	ACharacter* HerdLeader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Herd")
	TArray<ACharacter*> NearbyHerdMembers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Herd")
	float HerdCohesionRange;

	// AI timers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float BehaviorChangeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float NextBehaviorChangeTime;

private:
	void UpdateBehavior(float DeltaTime);
	void ProcessRadiationEffects(float DeltaTime);
	void UpdateBioluminescence(float DeltaTime);
	void CheckForHerdCohesion();
};
