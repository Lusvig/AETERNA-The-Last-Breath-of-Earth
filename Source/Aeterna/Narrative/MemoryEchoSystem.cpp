#include "MemoryEchoSystem.h"

AMemoryEchoSystem::AMemoryEchoSystem()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	CurrentlyPlayingEchoID = -1;
	EchoPlaybackTime = 0.0f;
}

void AMemoryEchoSystem::BeginPlay()
{
	Super::BeginPlay();

	InitializeDefaultEchoes();

	UE_LOG(LogTemp, Warning, TEXT("MemoryEchoSystem initialized with %d echoes"), AllEchoes.Num());
}

void AMemoryEchoSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle echo playback timing
	if (CurrentlyPlayingEchoID >= 0)
	{
		EchoPlaybackTime += DeltaTime;

		FMemoryEcho* CurrentEcho = nullptr;
		for (FMemoryEcho& Echo : AllEchoes)
		{
			if (Echo.EchoID == CurrentlyPlayingEchoID)
			{
				CurrentEcho = &Echo;
				break;
			}
		}

		if (CurrentEcho && EchoPlaybackTime >= CurrentEcho->DurationSeconds)
		{
			OnEchoCompleted.Broadcast(CurrentlyPlayingEchoID);
			CurrentlyPlayingEchoID = -1;
			EchoPlaybackTime = 0.0f;
		}
	}
}

void AMemoryEchoSystem::RegisterEcho(const FMemoryEcho& NewEcho)
{
	AllEchoes.Add(NewEcho);
	UE_LOG(LogTemp, Warning, TEXT("Echo registered: %s (ID: %d)"), *NewEcho.EchoTitle, NewEcho.EchoID);
}

void AMemoryEchoSystem::TriggerEcho(int32 EchoID)
{
	FMemoryEcho* TargetEcho = nullptr;
	for (FMemoryEcho& Echo : AllEchoes)
	{
		if (Echo.EchoID == EchoID)
		{
			TargetEcho = &Echo;
			break;
		}
	}

	if (TargetEcho)
	{
		CurrentlyPlayingEchoID = EchoID;
		EchoPlaybackTime = 0.0f;
		TargetEcho->bHasBeenTriggered = true;

		OnEchoTriggered.Broadcast(EchoID);

		UE_LOG(LogTemp, Warning, TEXT("Echo triggered: %s"), *TargetEcho->EchoTitle);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Echo not found: %d"), EchoID);
	}
}

FMemoryEcho AMemoryEchoSystem::GetEcho(int32 EchoID)
{
	for (const FMemoryEcho& Echo : AllEchoes)
	{
		if (Echo.EchoID == EchoID)
		{
			return Echo;
		}
	}

	return FMemoryEcho();
}

TArray<FMemoryEcho> AMemoryEchoSystem::GetTriggeredEchoes() const
{
	TArray<FMemoryEcho> TriggeredEchoes;

	for (const FMemoryEcho& Echo : AllEchoes)
	{
		if (Echo.bHasBeenTriggered)
		{
			TriggeredEchoes.Add(Echo);
		}
	}

	return TriggeredEchoes;
}

bool AMemoryEchoSystem::HasEchoBeenTriggered(int32 EchoID) const
{
	for (const FMemoryEcho& Echo : AllEchoes)
	{
		if (Echo.EchoID == EchoID)
		{
			return Echo.bHasBeenTriggered;
		}
	}

	return false;
}

void AMemoryEchoSystem::MarkEchoTriggered(int32 EchoID)
{
	for (FMemoryEcho& Echo : AllEchoes)
	{
		if (Echo.EchoID == EchoID)
		{
			Echo.bHasBeenTriggered = true;
			return;
		}
	}
}

void AMemoryEchoSystem::InitializeDefaultEchoes()
{
	// Initialize with vertical slice echoes

	// Echo 1: Sarah Chen's Last Day
	FMemoryEcho SarahEcho;
	SarahEcho.EchoID = 1;
	SarahEcho.NPCName = TEXT("Sarah Chen");
	SarahEcho.EchoTitle = TEXT("Sarah's Last Day");
	SarahEcho.EchoDescription = TEXT("A marine biologist's final moments studying the bioluminescent organisms of Notre-Dame, grappling with loss and legacy.");
	SarahEcho.DurationSeconds = 405.0f; // 6:45
	SarahEcho.EchoLocation = FVector(0.0f, 0.0f, 0.0f); // Paris Notre-Dame
	SarahEcho.CinematicSequencePath = TEXT("/Game/Cinematics/MemoryEchoes/Sarah_LastDay");
	SarahEcho.MoralWeight = 3; // High importance
	RegisterEcho(SarahEcho);

	// Echo 2: Marcus's Betrayal
	FMemoryEcho MarcusEcho;
	MarcusEcho.EchoID = 2;
	MarcusEcho.NPCName = TEXT("Marcus");
	MarcusEcho.EchoTitle = TEXT("The Sacrifice");
	MarcusEcho.EchoDescription = TEXT("A settlement leader's terrible choice to sacrifice a family for the greater good, haunting him until the end.");
	MarcusEcho.DurationSeconds = 480.0f; // 8:00
	MarcusEcho.EchoLocation = FVector(0.0f, 0.0f, 0.0f); // Venice
	MarcusEcho.CinematicSequencePath = TEXT("/Game/Cinematics/MemoryEchoes/Marcus_Betrayal");
	MarcusEcho.MoralWeight = 4; // Highest importance
	RegisterEcho(MarcusEcho);

	// Echo 3: The Child's Hope
	FMemoryEcho ChildEcho;
	ChildEcho.EchoID = 3;
	ChildEcho.NPCName = TEXT("Unknown Child");
	ChildEcho.EchoTitle = TEXT("A Child's Drawing");
	ChildEcho.EchoDescription = TEXT("A young girl teaches other children about hope while slowly succumbing to illness, surrounded by her artwork.");
	ChildEcho.DurationSeconds = 300.0f; // 5:00
	ChildEcho.EchoLocation = FVector(0.0f, 0.0f, 0.0f); // Alpine Refuge
	ChildEcho.CinematicSequencePath = TEXT("/Game/Cinematics/MemoryEchoes/Child_Hope");
	ChildEcho.MoralWeight = 5; // Critically important
	RegisterEcho(ChildEcho);

	// Echo 4: Dr. Okonkwo's Mission
	FMemoryEcho DoctorEcho;
	DoctorEcho.EchoID = 4;
	DoctorEcho.NPCName = TEXT("Dr. Okonkwo");
	DoctorEcho.EchoTitle = TEXT("The Last Scientist");
	DoctorEcho.EchoDescription = TEXT("A scientist devoted her final days to understanding the atmosphere's collapse, hoping her research might save what remains.");
	DoctorEcho.DurationSeconds = 420.0f; // 7:00
	DoctorEcho.EchoLocation = FVector(0.0f, 0.0f, 0.0f); // Chernobyl Underground Lab
	DoctorEcho.CinematicSequencePath = TEXT("/Game/Cinematics/MemoryEchoes/Doctor_Mission");
	DoctorEcho.MoralWeight = 3;
	RegisterEcho(DoctorEcho);

	UE_LOG(LogTemp, Warning, TEXT("Default echoes initialized: %d echoes loaded"), AllEchoes.Num());
}
