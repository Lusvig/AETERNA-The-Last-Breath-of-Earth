#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PsychologicalSystem.generated.h"

// Psychological states
UENUM(BlueprintType)
enum class EPsychologicalState : uint8
{
	Stable = 0			UMETA(DisplayName = "Stable"),
	Anxious = 1			UMETA(DisplayName = "Anxious"),
	Paranoid = 2		UMETA(DisplayName = "Paranoid"),
	Desperate = 3		UMETA(DisplayName = "Desperate"),
	Hallucinating = 4	UMETA(DisplayName = "Hallucinating"),
	Broken = 5			UMETA(DisplayName = "Psychologically Broken")
};

// Specific trauma types
UENUM(BlueprintType)
enum class ETraumaType : uint8
{
	Witnessed_Death = 0		UMETA(DisplayName = "Witnessed Death"),
	Mass_Grave = 1			UMETA(DisplayName = "Found Mass Grave"),
	Starvation = 2			UMETA(DisplayName = "Near Starvation"),
	Drowning = 3			UMETA(DisplayName = "Near Drowning"),
	Radiation = 4			UMETA(DisplayName = "Radiation Exposure"),
	Isolation = 5			UMETA(DisplayName = "Extreme Isolation"),
	Loss = 6				UMETA(DisplayName = "Loss of Companion"),
	Cannibalism = 7			UMETA(DisplayName = "Cannibalism"))
};

/**
 * UPsychologicalSystem
 * Handles psychological breakdown, trauma accumulation, hallucinations
 * THE HUMAN COST OF SURVIVAL
 */
UCLASS(ClassGroup = (Aeterna), meta = (BlueprintSpawnableComponent))
class AETERNA_API UPsychologicalSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UPsychologicalSystem();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Psychology")
	float GetSanityLevel() const { return SanityLevel; }

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	EPsychologicalState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	float GetTraumaLevel() const { return TraumaLevel; }

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	bool IsHallucinating() const { return bIsHallucinating; }

	// Trauma triggers
	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void InflictTrauma(ETraumaType TraumaType, float Severity = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void InflictIsolationTrauma(float TimeAloneSeconds);

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void WitnessDeath(AActor* DeadNPC);

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void FindMassGrave(int32 BodyCount);

	// Breakdown mechanics
	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void TriggerHallucination();

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void TriggerParanoia();

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void TriggerDespair();

	// Coping mechanisms
	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void FindComfort(const FString& ComfortSource);

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void ExperienceBeauty(); // Seeing something beautiful reduces trauma

	UFUNCTION(BlueprintCallable, Category = "Psychology")
	void SocialInteraction(); // Talking to NPCs helps sanity

	// Events
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPsychologicalStateChanged, EPsychologicalState);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHallucinationTriggered, ETraumaType);
	DECLARE_MULTICAST_DELEGATE(FOnBreakdown);
	DECLARE_MULTICAST_DELEGATE(FOnSuicideThought);

	FOnPsychologicalStateChanged OnStateChanged;
	FOnHallucinationTriggered OnHallucination;
	FOnBreakdown OnBreakdown;
	FOnSuicideThought OnSuicideThought;

protected:
	// Core psychological state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float SanityLevel; // 0-100, 50 is baseline

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	EPsychologicalState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float TraumaLevel; // 0-100, accumulates over time

	// Trauma tracking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	TMap<ETraumaType, float> TraumaHistory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float AccumulatedDeathWitnesses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float IsolationTime; // Seconds alone without NPC contact

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float LastSocialInteractionTime;

	// Psychological state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	bool bIsHallucinating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float HallucinationIntensity; // 0-1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	ETraumaType LastHallucinationSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float ParanoiaLevel; // 0-100, affects NPC trust perception

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float DespairLevel; // 0-100, affects movement speed and motivation

	// Breakdown mechanics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	int32 BreakdownCount; // How many times player has had breakdown

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float TimeSinceLastBreakdown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	bool bSuicidalThoughtsActive;

	// Hallucination details
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	FString HallucinationDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float HallucinationDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psychology")
	float HallucinationTimer;

	// Audio/VFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	bool bHeartbeatAudioPlaying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	bool bDistortedAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	bool bScreenDistortion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	float ScreenDistortionIntensity; // 0-1

private:
	void UpdatePsychologicalState(float DeltaTime);
	void CheckForBreakdown();
	void ApplyHallucinationEffects(float DeltaTime);
	void UpdateIsolationTrauma(float DeltaTime);
	void CheckSuicideRisk();
};
