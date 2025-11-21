#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvivalManager.generated.h"

class USurvivalComponent;

/**
 * ASurvivalManager
 * Central manager for all survival mechanics, food resources, and crafting
 */
UCLASS()
class AETERNA_API ASurvivalManager : public AActor
{
	GENERATED_BODY()

public:
	ASurvivalManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Food management
	UFUNCTION(BlueprintCallable, Category = "Survival")
	void RegisterFoodSource(FString FoodName, float Nutrition, float Hydration, bool bIsSafe);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void ConsumeFoodSource(FString FoodName, USurvivalComponent* Consumer);

	// Resource tracking
	UFUNCTION(BlueprintCallable, Category = "Resources")
	int32 GetResourceCount(FString ResourceName) const;

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void AddResource(FString ResourceName, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void RemoveResource(FString ResourceName, int32 Count);

	// Environmental conditions
	UFUNCTION(BlueprintCallable, Category = "Environment")
	void SetAmbientTemperature(float Temperature);

	UFUNCTION(BlueprintCallable, Category = "Environment")
	float GetAmbientTemperature() const { return AmbientTemperature; }

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void SetRadiationLevel(float Level);

	UFUNCTION(BlueprintCallable, Category = "Environment")
	float GetRadiationLevel() const { return CurrentRadiationLevel; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float AmbientTemperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
	float CurrentRadiationLevel;

	UPROPERTY()
	TMap<FString, int32> ResourceInventory;

	UPROPERTY()
	TMap<FString, float> FoodSourcesNutrition;
};
