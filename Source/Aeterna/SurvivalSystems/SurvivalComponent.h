#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalComponent.generated.h"

// Survival stat types
UENUM(BlueprintType)
enum class ESurvivalStat : uint8
{
	Hunger = 0		UMETA(DisplayName = "Hunger"),
	Thirst = 1		UMETA(DisplayName = "Thirst"),
	Cold = 2		UMETA(DisplayName = "Cold"),
	Radiation = 3	UMETA(DisplayName = "Radiation"),
	Injury = 4		UMETA(DisplayName = "Injury"),
	Exhaustion = 5	UMETA(DisplayName = "Exhaustion"),
	Sanity = 6		UMETA(DisplayName = "Sanity"),
	Health = 7		UMETA(DisplayName = "Health")
};

// Survival stat structure
USTRUCT(BlueprintType)
struct FSurvivalStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	float DecayRate; // How fast the stat worsens per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FString StatName;

	FSurvivalStat()
		: CurrentValue(50.0f), MaxValue(100.0f), DecayRate(0.1f), StatName(TEXT("Unnamed"))
	{
	}
};

/**
 * USurvivalComponent
 * Handles all player survival stat tracking and interactions
 */
UCLASS(ClassGroup = (Aeterna), meta = (BlueprintSpawnableComponent))
class AETERNA_API USurvivalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USurvivalComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Survival")
	float GetStat(ESurvivalStat StatType) const;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	FSurvivalStat GetFullStat(ESurvivalStat StatType) const;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	bool IsHealthy() const;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	bool IsCritical() const; // At least one stat is critically low

	// Setters/Modifiers
	UFUNCTION(BlueprintCallable, Category = "Survival")
	void ApplyDamage(ESurvivalStat StatType, float Amount);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void Restore(ESurvivalStat StatType, float Amount);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void EatFood(float Nutrition, float Hydration = 0.0f, bool bIsClean = true);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void DrinkWater(float Amount, bool bIsSafe = true);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void GetWarmth(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void ExposeToRadiation(float RadiationAmount);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void TakeDamage(float Amount, bool bIsRadiation = false);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void Rest(float Duration);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void InflictPsychologicalTrauma(float Amount);

	// Events
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, ESurvivalStat, float);
	DECLARE_MULTICAST_DELEGATE(FOnDeath);
	DECLARE_MULTICAST_DELEGATE(FOnCritical);

	FOnStatChanged OnStatChanged;
	FOnDeath OnDeath;
	FOnCritical OnCritical;

protected:
	// Survival stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FSurvivalStat HungerStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FSurvivalStat ThirstStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FSurvivalStat ColdStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FSurvivalStat RadiationStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FSurvivalStat InjuryStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FSurvivalStat ExhaustionStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FSurvivalStat SanityStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
	FSurvivalStat HealthStat;

private:
	void UpdateStats(float DeltaTime);
	void CheckForDeath();
	void CheckForCritical();
	void ApplyStatInteractions(); // Stats affect each other
};
