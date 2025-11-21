#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/List.h"
#include "MemoryEchoCinematic.generated.h"

class ACharacter;
class APlayerController;

// Memory Echo cinematic event
USTRUCT(BlueprintType)
struct FMemoryEchoCinematicEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Echo")
	float TimeInSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Echo")
	FString EventType; // "dialogue", "emotion", "flashback", "sound"

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Echo")
	FText EventContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Echo")
	float EmotionalWeight; // 0-1, how intense this moment is

	FMemoryEchoCinematicEvent()
		: TimeInSequence(0.0f), EventType(TEXT("")), EventContent(FText()), EmotionalWeight(0.5f)
	{
	}
};

/**
 * AMemoryEchoCinematic
 * Plays cinematically directed Memory Echo sequences
 * Full audio, camera direction, emotional beats
 */
UCLASS()
class AETERNA_API AMemoryEchoCinematic : public AActor
{
	GENERATED_BODY()

public:
	AMemoryEchoCinematic();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Playback control
	UFUNCTION(BlueprintCallable, Category = "Cinema tic")
	void PlayMemoryEcho(int32 EchoID);

	UFUNCTION(BlueprintCallable, Category = "Cinematic")
	void StopPlayback();

	UFUNCTION(BlueprintCallable, Category = "Cinematic")
	void PausePlayback();

	UFUNCTION(BlueprintCallable, Category = "Cinematic")
	void ResumePlayback();

	UFUNCTION(BlueprintCallable, Category = "Cinematic")
	void SkipToTime(float TimeInSeconds);

	// Status
	UFUNCTION(BlueprintCallable, Category = "Cinematic")
	bool IsPlaying() const { return bIsPlaying; }

	UFUNCTION(BlueprintCallable, Category = "Cinematic")
	float GetPlaybackProgress() const;

	UFUNCTION(BlueprintCallable, Category = "Cinematic")
	float GetTotalDuration() const { return TotalDuration; }

	// Audio
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetNarratorVO(const FString& AudioPath);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayDialogueLine(const FText& DialogueText, const FString& CharacterName, float Delay = 0.0f);

	// Camera
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraPath(const FString& CameraSequencePath);

	// Emotional beats
	UFUNCTION(BlueprintCallable, Category = "Emotion")
	void PlayEmotionalBeat(float EmotionalIntensity);

	// VFX
	UFUNCTION(BlueprintCallable, Category = "VFX")
	void PlayEchoEffect(const FString& EffectName, FVector Location);

	// Events
	DECLARE_MULTICAST_DELEGATE(FOnEchoStarted);
	DECLARE_MULTICAST_DELEGATE(FOnEchoCompleted);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueLine, const FText&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEmotionalBeat, float);

	FOnEchoStarted OnEchoStarted;
	FOnEchoCompleted OnEchoCompleted;
	FOnDialogueLine OnDialogueLine;
	FOnEmotionalBeat OnEmotionalBeat;

protected:
	// Playback state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	bool bIsPlaying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	bool bIsPaused;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	int32 CurrentEchoID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	float PlaybackTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	float TotalDuration;

	// Sequencing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	TArray<FMemoryEchoCinematicEvent> EchoEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
	int32 CurrentEventIndex;

	// Camera & perspective
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	ACharacter* CinematicCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FString CameraSequencePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraFOV;

	// Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	FString NarratorVOPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float AudioVolume;

	// Emotional state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
	float CurrentEmotionalIntensity; // 0-1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
	float EmotionalRiseRate; // How quickly intensity changes

	// Display control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bShowSubtitles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bShowHUD;

	// Player reference
	UPROPERTY()
	APlayerController* PlayerController;

private:
	void ProcessEchoEvents(float DeltaTime);
	void UpdateCinematicCamera(float DeltaTime);
	void ApplyEmotionalEffects(float DeltaTime);
	void HidePlayerUI();
	void RestorePlayerUI();
};
