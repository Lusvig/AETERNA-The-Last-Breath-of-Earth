#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OxygenSystem.generated.h"

// Hypoxia severity stages
UENUM(BlueprintType)
enum class EHypoxiaSeverity : uint8
{
	None = 0			UMETA(DisplayName = "Normal"),
	Mild = 1			UMETA(DisplayName = "Mild"),
	Moderate = 2		UMETA(DisplayName = "Moderate"),
	Severe = 3			UMETA(DisplayName = "Severe"),
	Critical = 4		UMETA(DisplayName = "Critical")
};

/**
 * UOxygenSystem
 * Handles oxygen deprivation, hypoxia, and CO2 buildup mechanics
 * Creates genuinely terrifying drowning/suffocation experience
 */
UCLASS(ClassGroup = (Aeterna), meta = (BlueprintSpawnableComponent))
class AETERNA_API UOxygenSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UOxygenSystem();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	float GetOxygenLevel() const { return OxygenLevel; }

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	float GetCO2Level() const { return CO2Level; }

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	EHypoxiaSeverity GetHypoxiaSeverity() const { return CurrentSeverity; }

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	bool IsInWater() const { return bIsInWater; }

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	float GetTimeToLoss() const;

	// Setters
	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void SetInWater(bool bNewInWater, float WaterOxygenLevel = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void SetOxygenLevel(float NewLevel);

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void BreathIn(float OxygenAmount = 10.0f);

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void SuffocationDamage();

	// Environmental effects
	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void ApplyRadiationDamage(float RadiationLevel);

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void ApplySmokeInhalation(float SmokeAmount);

	// Events for UI/VFX
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHypoxiaStateChanged, EHypoxiaSeverity);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnOxygenChanged, float);
	DECLARE_MULTICAST_DELEGATE(FOnDrowning);
	DECLARE_MULTICAST_DELEGATE(FOnSuffocation);

	FOnHypoxiaStateChanged OnHypoxiaStateChanged;
	FOnOxygenChanged OnOxygenChanged;
	FOnDrowning OnDrowning;
	FOnSuffocation OnSuffocation;

protected:
	// Core oxygen mechanics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oxygen")
	float OxygenLevel; // 0-100

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oxygen")
	float MaxOxygenCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oxygen")
	float CO2Level; // 0-100 (toxic buildup)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oxygen")
	float OxygenDepletionRate; // How fast oxygen depletes (per second)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oxygen")
	float CO2ProductionRate; // How fast CO2 builds up

	// Water/drowning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oxygen")
	bool bIsInWater;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oxygen")
	float DrowningDepletionMultiplier; // How much faster oxygen depletes underwater

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oxygen")
	float WaterOxygenLevel; // Oxygen available in current water body

	// Hypoxia severity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hypoxia")
	EHypoxiaSeverity CurrentSeverity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hypoxia")
	float MildThreshold; // 70% oxygen
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hypoxia")
	float ModerateThreshold; // 50% oxygen

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hypoxia")
	float SevereThreshold; // 25% oxygen

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hypoxia")
	float CriticalThreshold; // 14% oxygen (consciousness fades)

	// Damage accumulation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HypoxiaDamagePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PsychologicalPanicRate; // Sanity loss per second at severe hypoxia

	// Environmental modifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	bool bIsInToxicZone; // Radiation or chemical exposure reducing oxygen

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float SmokeInhalationLevel; // 0-100, causes CO2 buildup and damage

	// Audio/VFX triggers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	bool bHeartbeatAudioActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float HeartbeatRate; // BPM that increases with hypoxia

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bTunnelVisionActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float TunnelVisionIntensity; // 0-1, increases as oxygen depletes

private:
	void UpdateHypoxiaState();
	void ApplyHypoxiaEffects(float DeltaTime);
	void UpdatePsychologicalState();
	EHypoxiaSeverity CalculateSeverity();
};
