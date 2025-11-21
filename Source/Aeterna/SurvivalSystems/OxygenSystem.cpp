#include "OxygenSystem.h"
#include "SurvivalComponent.h"

UOxygenSystem::UOxygenSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.05f; // 20 updates per second for smoothness

	// Initialize oxygen
	OxygenLevel = 100.0f;
	MaxOxygenCapacity = 100.0f;
	CO2Level = 0.0f;

	// Depletion rates (in normal air, oxygen depletes slowly)
	OxygenDepletionRate = 0.2f; // Depletes fully in ~8 minutes of normal activity
	CO2ProductionRate = 0.15f;

	// Water mechanics
	bIsInWater = false;
	DrowningDepletionMultiplier = 4.0f; // Oxygen depletes 4x faster underwater
	WaterOxygenLevel = 0.0f;

	// Thresholds for hypoxia
	MildThreshold = 70.0f;
	ModerateThreshold = 50.0f;
	SevereThreshold = 25.0f;
	CriticalThreshold = 14.0f; // Brain damage begins, consciousness fades

	CurrentSeverity = EHypoxiaSeverity::None;
	HypoxiaDamagePerSecond = 0.5f;
	PsychologicalPanicRate = 2.0f;

	bIsInToxicZone = false;
	SmokeInhalationLevel = 0.0f;

	bHeartbeatAudioActive = false;
	HeartbeatRate = 60.0f;

	bTunnelVisionActive = false;
	TunnelVisionIntensity = 0.0f;
}

void UOxygenSystem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("OxygenSystem initialized on %s"), *GetOwnerName());
}

void UOxygenSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update oxygen levels
	if (bIsInWater)
	{
		// Drowning mechanics: oxygen depletes from current reserves (no ambient air)
		OxygenLevel -= (OxygenDepletionRate * DrowningDepletionMultiplier * DeltaTime);
	}
	else
	{
		// In air: slow oxygen depletion, faster recovery if breathing clean air
		OxygenLevel -= (OxygenDepletionRate * DeltaTime);

		// Recovery if in clean air (low CO2)
		if (CO2Level < 20.0f)
		{
			OxygenLevel = FMath::Min(OxygenLevel + (0.1f * DeltaTime), MaxOxygenCapacity);
		}
	}

	// CO2 accumulation
	CO2Level += (CO2ProductionRate * DeltaTime);

	// Smoke inhalation causes CO2 spike
	if (SmokeInhalationLevel > 0.0f)
	{
		CO2Level += (SmokeInhalationLevel * 0.5f * DeltaTime);
		SmokeInhalationLevel = FMath::Max(0.0f, SmokeInhalationLevel - (0.1f * DeltaTime)); // Gradually clear
	}

	// CO2 damages oxygen efficiency
	OxygenLevel -= (CO2Level * 0.05f * DeltaTime);

	// Clamp values
	OxygenLevel = FMath::Clamp(OxygenLevel, 0.0f, MaxOxygenCapacity);
	CO2Level = FMath::Clamp(CO2Level, 0.0f, 100.0f);

	// Update hypoxia state
	UpdateHypoxiaState();

	// Apply physical and psychological effects
	ApplyHypoxiaEffects(DeltaTime);

	OnOxygenChanged.Broadcast(OxygenLevel);
}

void UOxygenSystem::SetInWater(bool bNewInWater, float NewWaterOxygenLevel)
{
	bIsInWater = bNewInWater;
	WaterOxygenLevel = NewWaterOxygenLevel;

	if (bIsInWater)
	{
		UE_LOG(LogTemp, Warning, TEXT("Drowning started. Oxygen depletion multiplier: %.1f"), DrowningDepletionMultiplier);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Surfaced. Oxygen depletion normal"));
	}
}

void UOxygenSystem::SetOxygenLevel(float NewLevel)
{
	OxygenLevel = FMath::Clamp(NewLevel, 0.0f, MaxOxygenCapacity);
	OnOxygenChanged.Broadcast(OxygenLevel);
}

void UOxygenSystem::BreathIn(float OxygenAmount)
{
	OxygenLevel = FMath::Min(OxygenLevel + OxygenAmount, MaxOxygenCapacity);
	CO2Level = FMath::Max(0.0f, CO2Level - (OxygenAmount * 0.5f)); // Reduce CO2
	OnOxygenChanged.Broadcast(OxygenLevel);
}

void UOxygenSystem::SuffocationDamage()
{
	if (USurvivalComponent* SurvivalComp = GetOwner()->FindComponentByClass<USurvivalComponent>())
	{
		SurvivalComp->TakeDamage(HypoxiaDamagePerSecond, true);
		SurvivalComp->InflictPsychologicalTrauma(PsychologicalPanicRate);
	}
}

void UOxygenSystem::ApplyRadiationDamage(float RadiationLevel)
{
	// High radiation damages lungs, reduces oxygen efficiency
	if (USurvivalComponent* SurvivalComp = GetOwner()->FindComponentByClass<USurvivalComponent>())
	{
		SurvivalComp->ExposeToRadiation(RadiationLevel * 0.5f);
	}

	// Radiation zones have lower oxygen (chemical reactions consuming it)
	OxygenDepletionRate *= (1.0f + RadiationLevel * 0.1f);
}

void UOxygenSystem::ApplySmokeInhalation(float SmokeAmount)
{
	SmokeInhalationLevel = FMath::Min(SmokeInhalationLevel + SmokeAmount, 100.0f);
	CO2Level += (SmokeAmount * 0.3f);
}

void UOxygenSystem::UpdateHypoxiaState()
{
	EHypoxiaSeverity NewSeverity = CalculateSeverity();

	if (NewSeverity != CurrentSeverity)
	{
		CurrentSeverity = NewSeverity;
		OnHypoxiaStateChanged.Broadcast(CurrentSeverity);

		switch (CurrentSeverity)
		{
		case EHypoxiaSeverity::None:
			bHeartbeatAudioActive = false;
			bTunnelVisionActive = false;
			break;
		case EHypoxiaSeverity::Mild:
			UE_LOG(LogTemp, Warning, TEXT("Mild hypoxia: slight discomfort"));
			bHeartbeatAudioActive = false;
			break;
		case EHypoxiaSeverity::Moderate:
			UE_LOG(LogTemp, Error, TEXT("Moderate hypoxia: breathing difficulty"));
			bHeartbeatAudioActive = true;
			HeartbeatRate = 90.0f;
			break;
		case EHypoxiaSeverity::Severe:
			UE_LOG(LogTemp, Error, TEXT("SEVERE HYPOXIA: dizziness, tunnel vision beginning"));
			bHeartbeatAudioActive = true;
			HeartbeatRate = 120.0f;
			bTunnelVisionActive = true;
			OnSuffocation.Broadcast();
			break;
		case EHypoxiaSeverity::Critical:
			UE_LOG(LogTemp, Error, TEXT("CRITICAL HYPOXIA: consciousness fading. ~30 seconds to loss of consciousness"));
			HeartbeatRate = 150.0f;
			TunnelVisionIntensity = 1.0f;
			OnDrowning.Broadcast();
			break;
		}
	}
}

EHypoxiaSeverity UOxygenSystem::CalculateSeverity()
{
	// Combine oxygen and CO2 to determine severity
	float EffectiveOxygen = OxygenLevel - (CO2Level * 0.3f);

	if (EffectiveOxygen > MildThreshold)
		return EHypoxiaSeverity::None;
	else if (EffectiveOxygen > ModerateThreshold)
		return EHypoxiaSeverity::Mild;
	else if (EffectiveOxygen > SevereThreshold)
		return EHypoxiaSeverity::Moderate;
	else if (EffectiveOxygen > CriticalThreshold)
		return EHypoxiaSeverity::Severe;
	else
		return EHypoxiaSeverity::Critical;
}

void UOxygenSystem::ApplyHypoxiaEffects(float DeltaTime)
{
	switch (CurrentSeverity)
	{
	case EHypoxiaSeverity::None:
		// No effects
		break;

	case EHypoxiaSeverity::Mild:
		// Subtle audio cues, slight UI tint
		// Minor psychological stress (sanity -0.1/sec)
		if (USurvivalComponent* SurvivalComp = GetOwner()->FindComponentByClass<USurvivalComponent>())
		{
			SurvivalComp->InflictPsychologicalTrauma(0.1f * DeltaTime);
		}
		break;

	case EHypoxiaSeverity::Moderate:
		// Heartbeat audio increases
		// Movement speed reduced
		// Screen tint blue
		if (USurvivalComponent* SurvivalComp = GetOwner()->FindComponentByClass<USurvivalComponent>())
		{
			SurvivalComp->ApplyDamage(ESurvivalStat::Health, 0.2f * DeltaTime);
			SurvivalComp->InflictPsychologicalTrauma(0.5f * DeltaTime);
		}
		break;

	case EHypoxiaSeverity::Severe:
		// Tunnel vision activates (vignette effect)
		// Screen desaturates
		// Movement erratic
		// Severe panic
		TunnelVisionIntensity = FMath::Min(TunnelVisionIntensity + (0.2f * DeltaTime), 0.6f);
		
		if (USurvivalComponent* SurvivalComp = GetOwner()->FindComponentByClass<USurvivalComponent>())
		{
			SurvivalComp->ApplyDamage(ESurvivalStat::Health, 0.5f * DeltaTime);
			SurvivalComp->InflictPsychologicalTrauma(2.0f * DeltaTime);
		}
		break;

	case EHypoxiaSeverity::Critical:
		// Full tunnel vision
		// Black screen edges closing in
		// Heartbeat slowing (death approaching)
		// Extreme audio distortion
		// Severe health damage (10x normal)
		TunnelVisionIntensity = 1.0f;
		
		if (USurvivalComponent* SurvivalComp = GetOwner()->FindComponentByClass<USurvivalComponent>())
		{
			SurvivalComp->ApplyDamage(ESurvivalStat::Health, 5.0f * DeltaTime);
			SurvivalComp->InflictPsychologicalTrauma(5.0f * DeltaTime);
		}

		// If oxygen reaches 0, immediate death
		if (OxygenLevel <= 0.0f)
		{
			if (USurvivalComponent* SurvivalComp = GetOwner()->FindComponentByClass<USurvivalComponent>())
			{
				SurvivalComp->ApplyDamage(ESurvivalStat::Health, 100.0f); // Instant death
				UE_LOG(LogTemp, Error, TEXT("DEATH: Oxygen depletion"));
			}
		}
		break;
	}
}

void UOxygenSystem::UpdatePsychologicalState()
{
	// Drowning/suffocation is deeply traumatic
	// At critical levels, player experiences existential dread
	// Even after recovery, permanent sanity penalty
}

float UOxygenSystem::GetTimeToLoss() const
{
	if (OxygenLevel <= CriticalThreshold)
	{
		// At critical levels: ~30 seconds to unconsciousness
		return 30.0f - (OxygenLevel / CriticalThreshold * 30.0f);
	}
	
	// Estimate time to critical at current depletion rate
	float TimeToLoss = (OxygenLevel - CriticalThreshold) / OxygenDepletionRate;
	if (bIsInWater)
	{
		TimeToLoss /= DrowningDepletionMultiplier;
	}

	return TimeToLoss;
}
