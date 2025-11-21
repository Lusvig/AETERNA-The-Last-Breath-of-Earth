#include "SurvivalComponent.h"

USurvivalComponent::USurvivalComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1f; // Update every 0.1s

	// Initialize hunger stat (0-100, starts at 50)
	HungerStat.CurrentValue = 50.0f;
	HungerStat.MaxValue = 100.0f;
	HungerStat.DecayRate = 0.5f; // Mild decay without activity
	HungerStat.StatName = TEXT("Hunger");

	// Initialize thirst stat (decays faster than hunger)
	ThirstStat.CurrentValue = 50.0f;
	ThirstStat.MaxValue = 100.0f;
	ThirstStat.DecayRate = 0.8f;
	ThirstStat.StatName = TEXT("Thirst");

	// Initialize cold stat (depends on environment and clothing)
	ColdStat.CurrentValue = 0.0f;
	ColdStat.MaxValue = 100.0f;
	ColdStat.DecayRate = 0.3f;
	ColdStat.StatName = TEXT("Cold/Heat");

	// Radiation (never decreases)
	RadiationStat.CurrentValue = 0.0f;
	RadiationStat.MaxValue = 100.0f;
	RadiationStat.DecayRate = 0.0f;
	RadiationStat.StatName = TEXT("Radiation Exposure");

	// Injury tracking
	InjuryStat.CurrentValue = 0.0f;
	InjuryStat.MaxValue = 100.0f;
	InjuryStat.DecayRate = -0.2f; // Slowly heals if resting
	InjuryStat.StatName = TEXT("Injury");

	// Exhaustion
	ExhaustionStat.CurrentValue = 0.0f;
	ExhaustionStat.MaxValue = 100.0f;
	ExhaustionStat.DecayRate = 0.5f; // Slowly builds during activity
	ExhaustionStat.StatName = TEXT("Exhaustion");

	// Sanity (starts neutral)
	SanityStat.CurrentValue = 50.0f;
	SanityStat.MaxValue = 100.0f;
	SanityStat.DecayRate = 0.1f; // Mild decay from stress
	SanityStat.StatName = TEXT("Sanity");

	// Overall health (aggregated from other stats)
	HealthStat.CurrentValue = 100.0f;
	HealthStat.MaxValue = 100.0f;
	HealthStat.DecayRate = 0.0f; // Calculated from other stats
	HealthStat.StatName = TEXT("Health");
}

void USurvivalComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("SurvivalComponent initialized for %s"), *GetOwnerName());
}

void USurvivalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStats(DeltaTime);
	ApplyStatInteractions();
	CheckForCritical();
	CheckForDeath();
}

float USurvivalComponent::GetStat(ESurvivalStat StatType) const
{
	switch (StatType)
	{
	case ESurvivalStat::Hunger:
		return HungerStat.CurrentValue;
	case ESurvivalStat::Thirst:
		return ThirstStat.CurrentValue;
	case ESurvivalStat::Cold:
		return ColdStat.CurrentValue;
	case ESurvivalStat::Radiation:
		return RadiationStat.CurrentValue;
	case ESurvivalStat::Injury:
		return InjuryStat.CurrentValue;
	case ESurvivalStat::Exhaustion:
		return ExhaustionStat.CurrentValue;
	case ESurvivalStat::Sanity:
		return SanityStat.CurrentValue;
	case ESurvivalStat::Health:
		return HealthStat.CurrentValue;
	default:
		return 0.0f;
	}
}

FSurvivalStat USurvivalComponent::GetFullStat(ESurvivalStat StatType) const
{
	switch (StatType)
	{
	case ESurvivalStat::Hunger:
		return HungerStat;
	case ESurvivalStat::Thirst:
		return ThirstStat;
	case ESurvivalStat::Cold:
		return ColdStat;
	case ESurvivalStat::Radiation:
		return RadiationStat;
	case ESurvivalStat::Injury:
		return InjuryStat;
	case ESurvivalStat::Exhaustion:
		return ExhaustionStat;
	case ESurvivalStat::Sanity:
		return SanityStat;
	case ESurvivalStat::Health:
		return HealthStat;
	default:
		return FSurvivalStat();
	}
}

bool USurvivalComponent::IsDead() const
{
	return HealthStat.CurrentValue <= 0.0f;
}

bool USurvivalComponent::IsHealthy() const
{
	return HealthStat.CurrentValue >= 75.0f && HungerStat.CurrentValue >= 40.0f && ThirstStat.CurrentValue >= 40.0f;
}

bool USurvivalComponent::IsCritical() const
{
	return HungerStat.CurrentValue < 10.0f || ThirstStat.CurrentValue < 10.0f || HealthStat.CurrentValue < 30.0f || RadiationStat.CurrentValue > 80.0f;
}

void USurvivalComponent::ApplyDamage(ESurvivalStat StatType, float Amount)
{
	switch (StatType)
	{
	case ESurvivalStat::Hunger:
		HungerStat.CurrentValue = FMath::Clamp(HungerStat.CurrentValue - Amount, 0.0f, HungerStat.MaxValue);
		break;
	case ESurvivalStat::Thirst:
		ThirstStat.CurrentValue = FMath::Clamp(ThirstStat.CurrentValue - Amount, 0.0f, ThirstStat.MaxValue);
		break;
	case ESurvivalStat::Cold:
		ColdStat.CurrentValue = FMath::Clamp(ColdStat.CurrentValue + Amount, -50.0f, 50.0f);
		break;
	case ESurvivalStat::Radiation:
		RadiationStat.CurrentValue = FMath::Clamp(RadiationStat.CurrentValue + Amount, 0.0f, RadiationStat.MaxValue);
		break;
	case ESurvivalStat::Injury:
		InjuryStat.CurrentValue = FMath::Clamp(InjuryStat.CurrentValue + Amount, 0.0f, InjuryStat.MaxValue);
		break;
	case ESurvivalStat::Exhaustion:
		ExhaustionStat.CurrentValue = FMath::Clamp(ExhaustionStat.CurrentValue + Amount, 0.0f, ExhaustionStat.MaxValue);
		break;
	case ESurvivalStat::Sanity:
		SanityStat.CurrentValue = FMath::Clamp(SanityStat.CurrentValue - Amount, 0.0f, SanityStat.MaxValue);
		break;
	case ESurvivalStat::Health:
		HealthStat.CurrentValue = FMath::Clamp(HealthStat.CurrentValue - Amount, 0.0f, HealthStat.MaxValue);
		break;
	}

	OnStatChanged.Broadcast(StatType, GetStat(StatType));
}

void USurvivalComponent::Restore(ESurvivalStat StatType, float Amount)
{
	switch (StatType)
	{
	case ESurvivalStat::Hunger:
		HungerStat.CurrentValue = FMath::Clamp(HungerStat.CurrentValue + Amount, 0.0f, HungerStat.MaxValue);
		break;
	case ESurvivalStat::Thirst:
		ThirstStat.CurrentValue = FMath::Clamp(ThirstStat.CurrentValue + Amount, 0.0f, ThirstStat.MaxValue);
		break;
	case ESurvivalStat::Exhaustion:
		ExhaustionStat.CurrentValue = FMath::Clamp(ExhaustionStat.CurrentValue - Amount, 0.0f, ExhaustionStat.MaxValue);
		break;
	case ESurvivalStat::Sanity:
		SanityStat.CurrentValue = FMath::Clamp(SanityStat.CurrentValue + Amount, 0.0f, SanityStat.MaxValue);
		break;
	case ESurvivalStat::Health:
		HealthStat.CurrentValue = FMath::Clamp(HealthStat.CurrentValue + Amount, 0.0f, HealthStat.MaxValue);
		break;
	default:
		break;
	}

	OnStatChanged.Broadcast(StatType, GetStat(StatType));
}

void USurvivalComponent::EatFood(float Nutrition, float Hydration, bool bIsClean)
{
	Restore(ESurvivalStat::Hunger, Nutrition);

	if (Hydration > 0.0f)
	{
		Restore(ESurvivalStat::Thirst, Hydration);
	}

	if (!bIsClean)
	{
		ApplyDamage(ESurvivalStat::Health, 5.0f); // Disease risk from unclean food
	}

	UE_LOG(LogTemp, Warning, TEXT("Food consumed: Nutrition +%.1f, Hydration +%.1f, Clean: %d"), Nutrition, Hydration, bIsClean);
}

void USurvivalComponent::DrinkWater(float Amount, bool bIsSafe)
{
	Restore(ESurvivalStat::Thirst, Amount);

	if (!bIsSafe)
	{
		ApplyDamage(ESurvivalStat::Health, 3.0f); // Contamination risk
	}

	UE_LOG(LogTemp, Warning, TEXT("Water consumed: +%.1f, Safe: %d"), Amount, bIsSafe);
}

void USurvivalComponent::GetWarmth(float Amount)
{
	ColdStat.CurrentValue = FMath::Clamp(ColdStat.CurrentValue + Amount, -50.0f, 50.0f);
	OnStatChanged.Broadcast(ESurvivalStat::Cold, ColdStat.CurrentValue);

	UE_LOG(LogTemp, Warning, TEXT("Warmth gained: %.1f"), Amount);
}

void USurvivalComponent::ExposeToRadiation(float RadiationAmount)
{
	RadiationStat.CurrentValue = FMath::Clamp(RadiationStat.CurrentValue + RadiationAmount, 0.0f, RadiationStat.MaxValue);
	OnStatChanged.Broadcast(ESurvivalStat::Radiation, RadiationStat.CurrentValue);

	UE_LOG(LogTemp, Warning, TEXT("Radiation exposure: +%.1f (Total: %.1f)"), RadiationAmount, RadiationStat.CurrentValue);
}

void USurvivalComponent::TakeDamage(float Amount, bool bIsRadiation)
{
	ApplyDamage(ESurvivalStat::Health, Amount);

	if (bIsRadiation)
	{
		ExposeToRadiation(Amount * 0.5f);
	}

	UE_LOG(LogTemp, Warning, TEXT("Damage taken: %.1f"), Amount);
}

void USurvivalComponent::Rest(float Duration)
{
	// Rest reduces exhaustion and slowly heals injuries
	float HealAmount = Duration * 0.5f; // 30% heal rate per second
	Restore(ESurvivalStat::Exhaustion, HealAmount);
	Restore(ESurvivalStat::Health, HealAmount * 0.5f);

	// Hunger increases while resting
	ApplyDamage(ESurvivalStat::Hunger, Duration * 0.2f);

	UE_LOG(LogTemp, Warning, TEXT("Rested for %.1f seconds"), Duration);
}

void USurvivalComponent::InflictPsychologicalTrauma(float Amount)
{
	ApplyDamage(ESurvivalStat::Sanity, Amount);

	if (SanityStat.CurrentValue < 30.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("CRITICAL SANITY: %.1f"), SanityStat.CurrentValue);
	}
}

void USurvivalComponent::UpdateStats(float DeltaTime)
{
	// Hunger increases over time
	HungerStat.CurrentValue = FMath::Clamp(HungerStat.CurrentValue - (HungerStat.DecayRate * DeltaTime), 0.0f, HungerStat.MaxValue);

	// Thirst increases faster
	ThirstStat.CurrentValue = FMath::Clamp(ThirstStat.CurrentValue - (ThirstStat.DecayRate * DeltaTime), 0.0f, ThirstStat.MaxValue);

	// Exhaustion slowly decreases naturally over time
	ExhaustionStat.CurrentValue = FMath::Clamp(ExhaustionStat.CurrentValue - (0.1f * DeltaTime), 0.0f, ExhaustionStat.MaxValue);

	// Sanity slowly decreases from stress
	SanityStat.CurrentValue = FMath::Clamp(SanityStat.CurrentValue - (SanityStat.DecayRate * DeltaTime), 0.0f, SanityStat.MaxValue);
}

void USurvivalComponent::ApplyStatInteractions()
{
	// If hungry, lose health faster
	if (HungerStat.CurrentValue < 20.0f)
	{
		HealthStat.CurrentValue -= 0.1f;
	}

	// If thirsty, lose health even faster
	if (ThirstStat.CurrentValue < 15.0f)
	{
		HealthStat.CurrentValue -= 0.2f;
	}

	// If extremely cold, lose health rapidly
	if (ColdStat.CurrentValue < -30.0f)
	{
		HealthStat.CurrentValue -= 0.5f;
	}

	// If highly radiated, lose health
	if (RadiationStat.CurrentValue > 75.0f)
	{
		HealthStat.CurrentValue -= 0.15f;
	}

	// Exhaustion affects sanity negatively
	if (ExhaustionStat.CurrentValue > 80.0f)
	{
		SanityStat.CurrentValue -= 0.05f;
	}

	HealthStat.CurrentValue = FMath::Clamp(HealthStat.CurrentValue, 0.0f, HealthStat.MaxValue);
}

void USurvivalComponent::CheckForCritical()
{
	if (IsCritical())
	{
		OnCritical.Broadcast();
		UE_LOG(LogTemp, Error, TEXT("CRITICAL CONDITION: Player in danger!"));
	}
}

void USurvivalComponent::CheckForDeath()
{
	if (IsDead())
	{
		OnDeath.Broadcast();
		UE_LOG(LogTemp, Error, TEXT("PLAYER DEAD: Game Over"));

		// TODO: Trigger death sequence, show ending
		if (AActor* Owner = GetOwner())
		{
			Owner->Destroy();
		}
	}
}
