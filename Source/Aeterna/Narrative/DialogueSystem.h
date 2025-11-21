#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueSystem.generated.h"

// Dialogue line structure
USTRUCT(BlueprintType)
struct FDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 LineID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float DisplayDuration; // In seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString AudioPath; // Path to VO file

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float EmotionalIntensity; // 0-1

	FDialogueLine()
		: LineID(0), SpeakerName(TEXT("")), DialogueText(FText()), DisplayDuration(0.0f),
		  AudioPath(TEXT("")), EmotionalIntensity(0.5f)
	{
	}
};

// Dialogue choice for player
USTRUCT(BlueprintType)
struct FDialogueChoice
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 ChoiceID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText ChoiceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 NextDialogueID; // Which dialogue to play after this choice

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float MoralWeight; // How this choice affects player alignment

	FDialogueChoice()
		: ChoiceID(0), ChoiceText(FText()), NextDialogueID(-1), MoralWeight(0.0f)
	{
	}
};

// Full dialogue exchange
USTRUCT(BlueprintType)
struct FDialogueExchange
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 ExchangeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString ContextNPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueLine> Lines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueChoice> PlayerChoices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsOneTime; // Can only play once

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bHasBeenPlayed;

	FDialogueExchange()
		: ExchangeID(0), ContextNPC(TEXT("")), bIsOneTime(false), bHasBeenPlayed(false)
	{
	}
};

/**
 * ADialogueSystem
 * Manages NPC dialogue, player choices, relationship impacts
 */
UCLASS()
class AETERNA_API ADialogueSystem : public AActor
{
	GENERATED_BODY()

public:
	ADialogueSystem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Dialogue playback
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogueExchange(int32 ExchangeID);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void PlayDialogueLine(const FDialogueLine& Line);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void EndDialogueExchange();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SelectDialogueChoice(int32 ChoiceID);

	// Status
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool IsDialogueActive() const { return bDialogueActive; }

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int32 GetCurrentExchangeID() const { return CurrentExchangeID; }

	// Relationship management
	UFUNCTION(BlueprintCallable, Category = "Relationships")
	void ModifyNPCRelationship(const FString& NPCName, float RelationshipChange);

	UFUNCTION(BlueprintCallable, Category = "Relationships")
	float GetNPCRelationship(const FString& NPCName) const;

	// Dialogue registration
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void RegisterDialogueExchange(const FDialogueExchange& Exchange);

	// Events
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueStarted, int32);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueEnded, int32);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLineDisplayed, const FText&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnChoicesPresented, const TArray<FDialogueChoice>&);

	FOnDialogueStarted OnDialogueStarted;
	FOnDialogueEnded OnDialogueEnded;
	FOnLineDisplayed OnLineDisplayed;
	FOnChoicesPresented OnChoicesPresented;

protected:
	// Active dialogue state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bDialogueActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 CurrentExchangeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 CurrentLineIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float LineDisplayTime;

	// Dialogue database
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<int32, FDialogueExchange> DialogueDatabase;

	// Relationship tracking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Relationships")
	TMap<FString, float> NPCRelationships;

	// Dialogue history
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<int32> PlayedDialogueExchanges;

private:
	void DisplayNextLine();
	void PresentChoices();
};
