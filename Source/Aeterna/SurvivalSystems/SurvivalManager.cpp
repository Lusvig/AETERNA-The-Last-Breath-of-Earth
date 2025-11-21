#include "SurvivalManager.h"
#include "SurvivalComponent.h"

ASurvivalManager::ASurvivalManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

	AmbientTemperature = 15.0f;
	CurrentRadiationLevel = 0.3f;
}

void ASurvivalManager::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("SurvivalManager initialized. Ambient Temp: %.1f°C, Radiation: %.2f"), AmbientTemperature, CurrentRadiationLevel);
}

void ASurvivalManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Could update environmental conditions over time here
}

void ASurvivalManager::RegisterFoodSource(FString FoodName, float Nutrition, float Hydration, bool bIsSafe)
{
	FoodSourcesNutrition.Add(FoodName, Nutrition);

	UE_LOG(LogTemp, Warning, TEXT("Food source registered: %s (Nutrition: %.1f, Hydration: %.1f, Safe: %d)"),
		   *FoodName, Nutrition, Hydration, bIsSafe);
}

void ASurvivalManager::ConsumeFoodSource(FString FoodName, USurvivalComponent* Consumer)
{
	if (!Consumer)
	{
		return;
	}

	float* NutritionPtr = FoodSourcesNutrition.Find(FoodName);
	if (NutritionPtr)
	{
		Consumer->EatFood(*NutritionPtr);
		UE_LOG(LogTemp, Warning, TEXT("%s consumed %s"), *Consumer->GetOwnerName(), *FoodName);
	}
}

int32 ASurvivalManager::GetResourceCount(FString ResourceName) const
{
	const int32* CountPtr = ResourceInventory.Find(ResourceName);
	return CountPtr ? *CountPtr : 0;
}

void ASurvivalManager::AddResource(FString ResourceName, int32 Count)
{
	int32* CountPtr = ResourceInventory.Find(ResourceName);
	if (CountPtr)
	{
		*CountPtr += Count;
	}
	else
	{
		ResourceInventory.Add(ResourceName, Count);
	}

	UE_LOG(LogTemp, Warning, TEXT("Resource added: %s x%d (Total: %d)"), *ResourceName, Count, GetResourceCount(ResourceName));
}

void ASurvivalManager::RemoveResource(FString ResourceName, int32 Count)
{
	int32* CountPtr = ResourceInventory.Find(ResourceName);
	if (CountPtr)
	{
		*CountPtr -= Count;
		if (*CountPtr < 0)
		{
			*CountPtr = 0;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Resource removed: %s x%d (Remaining: %d)"), *ResourceName, Count, GetResourceCount(ResourceName));
}

void ASurvivalManager::SetAmbientTemperature(float Temperature)
{
	AmbientTemperature = Temperature;
	UE_LOG(LogTemp, Warning, TEXT("Ambient temperature set to: %.1f°C"), AmbientTemperature);
}

void ASurvivalManager::SetRadiationLevel(float Level)
{
	CurrentRadiationLevel = FMath::Clamp(Level, 0.0f, 1.0f);
	UE_LOG(LogTemp, Warning, TEXT("Radiation level set to: %.2f"), CurrentRadiationLevel);
}
