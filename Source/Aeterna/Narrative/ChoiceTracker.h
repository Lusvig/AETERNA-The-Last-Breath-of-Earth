#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChoiceTracker.generated.h"

// Choice type enum
UENUM(BlueprintType)
enum class EChoiceType : uint8
{
	Moral = 0		UMETA(DisplayName = "Moral Choice"),
	Environmental = 1	UMETA(DisplayName = "Environmental Choice"),
	Social = 2		UMETA(DisplayName = "Social Choice"),
	Violence = 3	UMETA(DisplayName = "Violence"),
	Survival = 4	UMETA(DisplayName = "Survival Choice"),
	Narrative = 5	UMETA(DisplayName = "Narrative/Dialogue")
};

// Choice record structure
USTRUCT(BlueprintType)
struct FChoiceRecord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Choice")
	FString ChoiceDescription;

	UPROPERTY(BlueprintReadWrite, Category = "Choice")
	EChoiceType ChoiceType;

	UPROPERTY(BlueprintReadWrite, Category = "Choice")
	float Alignment; // -1.0 to 1.0 representing choice direction

	UPROPERTY(BlueprintReadWrite, Category = "Choice")
	float Weight; // Impact on ending calculation

	UPROPERTY(BlueprintReadWrite, Category = "Choice")
	int32 DayRecorded;

	UPROPERTY(BlueprintReadWrite, Category = "Choice")
	FVector LocationOfChoice;

	FChoiceRecord()
		: ChoiceDescription(TEXT("")), ChoiceType(EChoiceType::Moral), Alignment(0.0f), Weight(1.0f), DayRecorded(1), LocationOfChoice(FVector::ZeroVector)
	{
	}
};

// Ending calculation structure
USTRUCT(BlueprintType)
struct FEndingEligibility
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Ending")
	int32 EndingID;

	UPROPERTY(BlueprintReadWrite, Category = "Ending")
	FString EndingName;

	UPROPERTY(BlueprintReadWrite, Category = "Ending")
	float CompassionRequirement; // 0-100

	UPROPERTY(BlueprintReadWrite, Category = "Ending")
	float EnvironmentalRequirement; // -100 to 100

	UPROPERTY(BlueprintReadWrite, Category = "Ending")
	int32 MaxKillCount;

	UPROPERTY(BlueprintReadWrite, Category = "Ending")
	float TrustRatio; // 0-1

	UPROPERTY(BlueprintReadWrite, Category = "Ending")
	bool bIsEligible;
};

/**
 * AChoiceTracker
 * Tracks all player choices throughout the game and calculates ending eligibility
 */
UCLASS()
class AETERNA_API AChoiceTracker : public AActor
{
	GENERATED_BODY()

public:
	AChoiceTracker();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Record a choice
	UFUNCTION(BlueprintCallable, Category = "Choices")
	void RecordChoice(FString Description, float Alignment, float Weight = 1.0f, EChoiceType ChoiceType = EChoiceType::Moral);

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Choices")
	float GetCompassionScore() const { return CompassionScore; }

	UFUNCTION(BlueprintCallable, Category = "Choices")
	float GetEnvironmentalScore() const { return EnvironmentalScore; }

	UFUNCTION(BlueprintCallable, Category = "Choices")
	int32 GetKillCount() const { return KillCount; }

	UFUNCTION(BlueprintCallable, Category = "Choices")
	float GetTrustRatio() const { return TrustRatio; }

	UFUNCTION(BlueprintCallable, Category = "Choices")
	int32 GetTotalChoicesMade() const { return AllChoices.Num(); }

	// Ending calculation
	UFUNCTION(BlueprintCallable, Category = "Ending")
	int32 CalculateEndingIndex();

	UFUNCTION(BlueprintCallable, Category = "Ending")
	FEndingEligibility CheckEndingEligibility(int32 EndingID);

	UFUNCTION(BlueprintCallable, Category = "Ending")
	TArray<FEndingEligibility> GetAllEligibleEndings();

	// Record specific types
	UFUNCTION(BlueprintCallable, Category = "Choices")
	void RecordMoralChoice(bool bWasCompassionate, float Weight = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Choices")
	void RecordEnvironmentalChoice(bool bWasConservative, float Weight = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Choices")
	void RecordKill(bool bWasNecessary = false);

	UFUNCTION(BlueprintCallable, Category = "Choices")
	void RecordNPCInteraction(bool bWasTrustful, float Weight = 1.0f);

	// Get choice history
	UFUNCTION(BlueprintCallable, Category = "Choices")
	TArray<FChoiceRecord> GetChoiceHistory() const { return AllChoices; }

protected:
	// Core choice metrics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracking")
	float CompassionScore; // 0-100, starts at 50

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracking")
	float EnvironmentalScore; // -100 to 100, starts at 0

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracking")
	int32 KillCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracking")
	int32 TrustfulInteractions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracking")
	int32 BetrayalInteractions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracking")
	float TrustRatio; // (Trustful - Betrayal) / Total

	// All recorded choices
	UPROPERTY()
	TArray<FChoiceRecord> AllChoices;

	// Ending data
	UPROPERTY(EditAnywhere, Category = "Endings")
	int32 SelectedEndingID;

	UPROPERTY(EditAnywhere, Category = "Endings")
	FString SelectedEndingName;

private:
	int32 GetEndingTier();
};
