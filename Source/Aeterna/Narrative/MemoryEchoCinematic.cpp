#include "MemoryEchoCinematic.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMemoryEchoCinematic::AMemoryEchoCinematic()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.016f; // 60fps for smooth cinematics

	bIsPlaying = false;
	bIsPaused = false;
	CurrentEchoID = -1;
	PlaybackTime = 0.0f;
	TotalDuration = 0.0f;
	CurrentEventIndex = 0;

	CameraFOV = 75.0f;
	AudioVolume = 1.0f;

	CurrentEmotionalIntensity = 0.0f;
	EmotionalRiseRate = 0.5f;

	bShowSubtitles = true;
	bShowHUD = false;

	PlayerController = nullptr;
}

void AMemoryEchoCinematic::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UE_LOG(LogTemp, Warning, TEXT("MemoryEchoCinematic initialized"));
}

void AMemoryEchoCinematic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsPlaying || bIsPaused)
	{
		return;
	}

	PlaybackTime += DeltaTime;

	// Check if cinematic is complete
	if (PlaybackTime >= TotalDuration)
	{
		StopPlayback();
		return;
	}

	// Process events and update cinematics
	ProcessEchoEvents(DeltaTime);
	UpdateCinematicCamera(DeltaTime);
	ApplyEmotionalEffects(DeltaTime);
}

void AMemoryEchoCinematic::PlayMemoryEcho(int32 EchoID)
{
	CurrentEchoID = EchoID;
	PlaybackTime = 0.0f;
	CurrentEventIndex = 0;
	bIsPlaying = true;
	bIsPaused = false;

	// Hide player HUD
	HidePlayerUI();

	OnEchoStarted.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("Playing Memory Echo %d"), EchoID);

	// Example: Sarah's Last Day (6:45 = 405 seconds)
	if (EchoID == 1)
	{
		TotalDuration = 405.0f;

		// Build event sequence
		EchoEvents.Empty();

		// [0:00-1:20] Setup: Sarah in cathedral
		FMemoryEchoCinematicEvent Setup;
		Setup.TimeInSequence = 0.0f;
		Setup.EventType = TEXT("scene_setup");
		Setup.EventContent = FText::FromString(TEXT("Camera pans over flooded Notre-Dame cathedral"));
		Setup.EmotionalWeight = 0.3f;
		EchoEvents.Add(Setup);

		// [1:20-3:15] Crisis: Receives message about daughter
		FMemoryEchoCinematicEvent Crisis;
		Crisis.TimeInSequence = 80.0f;
		Crisis.EventType = TEXT("dialogue");
		Crisis.EventContent = FText::FromString(TEXT("Sarah reads: 'Emma's been gone for two weeks. They just told me now.'"));
		Crisis.EmotionalWeight = 0.9f;
		EchoEvents.Add(Crisis);

		// [3:15-4:45] Realization: Sarah decides her fate
		FMemoryEchoCinematicEvent Realization;
		Realization.TimeInSequence = 195.0f;
		Realization.EventType = TEXT("dialogue");
		Realization.EventContent = FText::FromString(TEXT("'I can't reach Emma in the world above. But maybe I can be useful down here.'"));
		Realization.EmotionalWeight = 0.85f;
		EchoEvents.Add(Realization);

		// [5:30-6:45] Final moment: Enters glowing water
		FMemoryEchoCinematicEvent Resolution;
		Resolution.TimeInSequence = 330.0f;
		Resolution.EventType = TEXT("final_moment");
		Resolution.EventContent = FText::FromString(TEXT("Sarah walks into the bioluminescent water. Peaceful acceptance."));
		Resolution.EmotionalWeight = 1.0f;
		EchoEvents.Add(Resolution);
	}
}

void AMemoryEchoCinematic::StopPlayback()
{
	bIsPlaying = false;
	PlaybackTime = 0.0f;
	CurrentEventIndex = 0;
	CurrentEmotionalIntensity = 0.0f;

	RestorePlayerUI();

	OnEchoCompleted.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("Memory Echo playback complete"));
}

void AMemoryEchoCinematic::PausePlayback()
{
	bIsPaused = true;
	UE_LOG(LogTemp, Warning, TEXT("Memory Echo paused at %.1f seconds"), PlaybackTime);
}

void AMemoryEchoCinematic::ResumePlayback()
{
	bIsPaused = false;
	UE_LOG(LogTemp, Warning, TEXT("Memory Echo resumed"));
}

void AMemoryEchoCinematic::SkipToTime(float TimeInSeconds)
{
	PlaybackTime = FMath::Clamp(TimeInSeconds, 0.0f, TotalDuration);
	UE_LOG(LogTemp, Warning, TEXT("Memory Echo skipped to %.1f seconds"), PlaybackTime);
}

float AMemoryEchoCinematic::GetPlaybackProgress() const
{
	if (TotalDuration <= 0.0f)
	{
		return 0.0f;
	}

	return PlaybackTime / TotalDuration;
}

void AMemoryEchoCinematic::SetNarratorVO(const FString& AudioPath)
{
	NarratorVOPath = AudioPath;
	UE_LOG(LogTemp, Warning, TEXT("Narrator VO set: %s"), *AudioPath);
}

void AMemoryEchoCinematic::PlayDialogueLine(const FText& DialogueText, const FString& CharacterName, float Delay)
{
	// TODO: Play dialogue with proper audio and subtitle timing
	OnDialogueLine.Broadcast(DialogueText);

	UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *CharacterName, *DialogueText.ToString());
}

void AMemoryEchoCinematic::SetCameraPath(const FString& CameraSequencePath)
{
	CameraSequencePath = CameraSequencePath;
	UE_LOG(LogTemp, Warning, TEXT("Camera path set: %s"), *CameraSequencePath);
}

void AMemoryEchoCinematic::PlayEmotionalBeat(float EmotionalIntensity)
{
	CurrentEmotionalIntensity = FMath::Clamp(EmotionalIntensity, 0.0f, 1.0f);
	OnEmotionalBeat.Broadcast(CurrentEmotionalIntensity);

	UE_LOG(LogTemp, Warning, TEXT("Emotional beat: %.2f"), CurrentEmotionalIntensity);
}

void AMemoryEchoCinematic::PlayEchoEffect(const FString& EffectName, FVector Location)
{
	// TODO: Spawn Niagara VFX at location
	UE_LOG(LogTemp, Warning, TEXT("Echo effect spawned: %s at %.0f, %.0f, %.0f"), 
		   *EffectName, Location.X, Location.Y, Location.Z);
}

void AMemoryEchoCinematic::ProcessEchoEvents(float DeltaTime)
{
	// Process events that occur at current playback time
	for (int32 i = CurrentEventIndex; i < EchoEvents.Num(); ++i)
	{
		if (EchoEvents[i].TimeInSequence <= PlaybackTime)
		{
			CurrentEventIndex = i;

			// Execute event
			if (EchoEvents[i].EventType == TEXT("dialogue"))
			{
				PlayDialogueLine(EchoEvents[i].EventContent, TEXT("NPC"));
				PlayEmotionalBeat(EchoEvents[i].EmotionalWeight);
			}
			else if (EchoEvents[i].EventType == TEXT("final_moment"))
			{
				PlayEmotionalBeat(1.0f);
				PlayEchoEffect(TEXT("Bioluminescent_Water"), FVector::ZeroVector);
			}
		}
		else
		{
			break; // No more events until later
		}
	}
}

void AMemoryEchoCinematic::UpdateCinematicCamera(float DeltaTime)
{
	// TODO: Move camera along cinematic path
	// Interpolate between key camera points based on playback time
	// Apply depth of field and other cinematic effects

	if (PlayerController)
	{
		// Smooth camera movement during cinematic
		// Camera should follow emotional beats and dialogue
	}
}

void AMemoryEchoCinematic::ApplyEmotionalEffects(float DeltaTime)
{
	// Modify post-process materials based on emotional intensity
	// High intensity: increased saturation, slight chromatic aberration, music swell
	// Lower intensity: desaturated, quiet

	if (CurrentEmotionalIntensity > 0.7f)
	{
		// INTENSE EMOTIONAL MOMENT
		// TODO: Music stabs, sound design emphasizes emotional beat
		// Camera might zoom in on character's face
		// Screen might vignette
	}
}

void AMemoryEchoCinematic::HidePlayerUI()
{
	bShowHUD = false;

	// Disable player movement
	if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (PlayerCharacter->GetCharacterMovement())
		{
			PlayerCharacter->GetCharacterMovement()->DisableMovement();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Player UI hidden, movement disabled"));
}

void AMemoryEchoCinematic::RestorePlayerUI()
{
	bShowHUD = true;

	// Re-enable player movement
	if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (PlayerCharacter->GetCharacterMovement())
		{
			PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Player UI restored, movement enabled"));
}
