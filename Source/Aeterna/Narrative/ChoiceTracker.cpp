#include "ChoiceTracker.h"
#include "Kismet/GameplayStatics.h"

AChoiceTracker::AChoiceTracker()
{
	PrimaryActorTick.bCanEverTick = false;

	CompassionScore = 50.0f;
	EnvironmentalScore = 0.0f;
	KillCount = 0;
	TrustfulInteractions = 0;
	BetrayalInteractions = 0;
	TrustRatio = 0.5f;
	SelectedEndingID = -1;
	SelectedEndingName = TEXT("Unknown");
}

void AChoiceTracker::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ChoiceTracker initialized"));
}

void AChoiceTracker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChoiceTracker::RecordChoice(FString Description, float Alignment, float Weight, EChoiceType ChoiceType)
{
	FChoiceRecord NewChoice;
	NewChoice.ChoiceDescription = Description;
	NewChoice.ChoiceType = ChoiceType;
	NewChoice.Alignment = Alignment;
	NewChoice.Weight = Weight;
	NewChoice.DayRecorded = 1; // TODO: Get actual day from GameMode
	NewChoice.LocationOfChoice = FVector::ZeroVector; // TODO: Get player location

	AllChoices.Add(NewChoice);

	UE_LOG(LogTemp, Warning, TEXT("Choice recorded: %s (Alignment: %.2f, Weight: %.2f)"), *Description, Alignment, Weight);
}

void AChoiceTracker::RecordMoralChoice(bool bWasCompassionate, float Weight)
{
	if (bWasCompassionate)
	{
		CompassionScore = FMath::Clamp(CompassionScore + (10.0f * Weight), 0.0f, 100.0f);
		RecordChoice(TEXT("Compassionate Choice"), 1.0f, Weight, EChoiceType::Moral);
	}
	else
	{
		CompassionScore = FMath::Clamp(CompassionScore - (10.0f * Weight), 0.0f, 100.0f);
		RecordChoice(TEXT("Pragmatic Choice"), -1.0f, Weight, EChoiceType::Moral);
	}

	UE_LOG(LogTemp, Warning, TEXT("Moral choice recorded. Compassion: %.1f"), CompassionScore);
}

void AChoiceTracker::RecordEnvironmentalChoice(bool bWasConservative, float Weight)
{
	if (bWasConservative)
	{
		EnvironmentalScore = FMath::Clamp(EnvironmentalScore + (10.0f * Weight), -100.0f, 100.0f);
		RecordChoice(TEXT("Conservative Environmental Choice"), 1.0f, Weight, EChoiceType::Environmental);
	}
	else
	{
		EnvironmentalScore = FMath::Clamp(EnvironmentalScore - (10.0f * Weight), -100.0f, 100.0f);
		RecordChoice(TEXT("Exploitative Environmental Choice"), -1.0f, Weight, EChoiceType::Environmental);
	}

	UE_LOG(LogTemp, Warning, TEXT("Environmental choice recorded. Score: %.1f"), EnvironmentalScore);
}

void AChoiceTracker::RecordKill(bool bWasNecessary)
{
	KillCount++;
	RecordChoice(TEXT("Kill"), bWasNecessary ? 0.0f : -1.0f, 1.0f, EChoiceType::Violence);

	UE_LOG(LogTemp, Error, TEXT("Kill recorded. Total kills: %d"), KillCount);
}

void AChoiceTracker::RecordNPCInteraction(bool bWasTrustful, float Weight)
{
	if (bWasTrustful)
	{
		TrustfulInteractions++;
		RecordChoice(TEXT("Trustful NPC Interaction"), 1.0f, Weight, EChoiceType::Social);
	}
	else
	{
		BetrayalInteractions++;
		RecordChoice(TEXT("Betrayal"), -1.0f, Weight, EChoiceType::Social);
	}

	int32 TotalInteractions = TrustfulInteractions + BetrayalInteractions;
	if (TotalInteractions > 0)
	{
		TrustRatio = (float)TrustfulInteractions / (float)TotalInteractions;
	}

	UE_LOG(LogTemp, Warning, TEXT("NPC interaction recorded. Trust Ratio: %.2f"), TrustRatio);
}

int32 AChoiceTracker::CalculateEndingIndex()
{
	// Determine ending based on metrics
	// This is a simplified version; full version would check all 27 endings

	FString EndingName = TEXT("Unknown");
	int32 EndingID = 0;

	// Compassion axis (0-100)
	FString CompassionTier = TEXT("Pragmatist");
	if (CompassionScore > 75.0f)
	{
		CompassionTier = TEXT("Idealist");
	}
	else if (CompassionScore > 25.0f)
	{
		CompassionTier = TEXT("Balanced");
	}

	// Environmental axis (-100 to 100)
	FString EnvironmentalTier = TEXT("Neutral");
	if (EnvironmentalScore > 50.0f)
	{
		EnvironmentalTier = TEXT("Caretaker");
	}
	else if (EnvironmentalScore < -25.0f)
	{
		EnvironmentalTier = TEXT("Despoiler");
	}

	// Violence axis
	FString ViolenceTier = TEXT("Realist");
	if (KillCount < 5)
	{
		ViolenceTier = TEXT("Pacifist");
	}
	else if (KillCount > 50)
	{
		ViolenceTier = TEXT("Killer");
	}

	// Trust axis
	FString TrustTier = TEXT("Complex");
	if (TrustRatio > 0.7f)
	{
		TrustTier = TEXT("Ally");
	}
	else if (TrustRatio < 0.4f)
	{
		TrustTier = TEXT("Traitor");
	}

	EndingName = CompassionTier + TEXT(" ") + EnvironmentalTier + TEXT(" ") + ViolenceTier + TEXT(" ") + TrustTier;

	UE_LOG(LogTemp, Warning, TEXT("ENDING CALCULATED: %s"), *EndingName);
	UE_LOG(LogTemp, Warning, TEXT("  Compassion: %.1f (%s)"), CompassionScore, *CompassionTier);
	UE_LOG(LogTemp, Warning, TEXT("  Environmental: %.1f (%s)"), EnvironmentalScore, *EnvironmentalTier);
	UE_LOG(LogTemp, Warning, TEXT("  Violence: %d kills (%s)"), KillCount, *ViolenceTier);
	UE_LOG(LogTemp, Warning, TEXT("  Trust: %.2f (%s)"), TrustRatio, *TrustTier);

	SelectedEndingName = EndingName;
	return EndingID;
}

FEndingEligibility AChoiceTracker::CheckEndingEligibility(int32 EndingID)
{
	FEndingEligibility Eligibility;
	Eligibility.EndingID = EndingID;

	// This would be populated from a data table in production
	// For now, simple hardcoded checks

	if (EndingID == 1) // "The Merged" ending
	{
		Eligibility.EndingName = TEXT("The Merged");
		Eligibility.CompassionRequirement = 76.0f;
		Eligibility.EnvironmentalRequirement = 51.0f;
		Eligibility.MaxKillCount = 5;
		Eligibility.TrustRatio = 0.7f;

		Eligibility.bIsEligible = (CompassionScore >= Eligibility.CompassionRequirement &&
									EnvironmentalScore >= Eligibility.EnvironmentalRequirement &&
									KillCount <= Eligibility.MaxKillCount &&
									TrustRatio >= Eligibility.TrustRatio);
	}
	else
	{
		Eligibility.EndingName = TEXT("Unknown");
		Eligibility.bIsEligible = false;
	}

	return Eligibility;
}

TArray<FEndingEligibility> AChoiceTracker::GetAllEligibleEndings()
{
	TArray<FEndingEligibility> EligibleEndings;

	// Check all 27 endings (simplified)
	for (int32 i = 1; i <= 27; i++)
	{
		FEndingEligibility Ending = CheckEndingEligibility(i);
		if (Ending.bIsEligible)
		{
			EligibleEndings.Add(Ending);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Total eligible endings: %d"), EligibleEndings.Num());

	return EligibleEndings;
}

int32 AChoiceTracker::GetEndingTier()
{
	// Placeholder for ending tier calculation
	return 0;
}
