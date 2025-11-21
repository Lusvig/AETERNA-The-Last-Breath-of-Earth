#include "DialogueSystem.h"

ADialogueSystem::ADialogueSystem()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	bDialogueActive = false;
	CurrentExchangeID = -1;
	CurrentLineIndex = 0;
	LineDisplayTime = 0.0f;
}

void ADialogueSystem::BeginPlay()
{
	Super::BeginPlay();

	// Initialize example dialogues
	
	// Dialogue 1: First NPC encounter
	FDialogueExchange FirstEncounter;
	FirstEncounter.ExchangeID = 1;
	FirstEncounter.ContextNPC = TEXT("Unknown Survivor");
	FirstEncounter.bIsOneTime = false;

	// Line 1
	FDialogueLine Line1;
	Line1.LineID = 1;
	Line1.SpeakerName = TEXT("Unknown Survivor");
	Line1.DialogueText = FText::FromString(TEXT("Hello? Is anyone there? I... I haven't heard another human voice in weeks."));
	Line1.DisplayDuration = 4.0f;
	Line1.EmotionalIntensity = 0.7f;
	FirstEncounter.Lines.Add(Line1);

	// Line 2
	FDialogueLine Line2;
	Line2.LineID = 2;
	Line2.SpeakerName = TEXT("Unknown Survivor");
	Line2.DialogueText = FText::FromString(TEXT("Are you... alive? Real? Or am I finally losing it?"));
	Line2.DisplayDuration = 3.0f;
	Line2.EmotionalIntensity = 0.8f;
	FirstEncounter.Lines.Add(Line2);

	// Player choices
	FDialogueChoice Choice1;
	Choice1.ChoiceID = 1;
	Choice1.ChoiceText = FText::FromString(TEXT("Help them. They need compassion."));
	Choice1.MoralWeight = 1.0f;
	Choice1.NextDialogueID = 2;
	FirstEncounter.PlayerChoices.Add(Choice1);

	FDialogueChoice Choice2;
	Choice2.ChoiceID = 2;
	Choice2.ChoiceText = FText::FromString(TEXT("Assess whether they're dangerous first."));
	Choice2.MoralWeight = -0.5f;
	Choice2.NextDialogueID = 3;
	FirstEncounter.PlayerChoices.Add(Choice2);

	FDialogueChoice Choice3;
	Choice3.ChoiceID = 3;
	Choice3.ChoiceText = FText::FromString(TEXT("Leave without responding."));
	Choice3.MoralWeight = -2.0f;
	Choice3.NextDialogueID = -1; // End dialogue
	FirstEncounter.PlayerChoices.Add(Choice3);

	RegisterDialogueExchange(FirstEncounter);

	// Initialize NPC relationships
	NPCRelationships.Add(TEXT("Unknown Survivor"), 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("DialogueSystem initialized"));
}

void ADialogueSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDialogueActive)
	{
		LineDisplayTime += DeltaTime;

		// Check if current line should end
		FDialogueExchange* CurrentExchange = DialogueDatabase.Find(CurrentExchangeID);
		if (CurrentExchange && CurrentLineIndex < CurrentExchange->Lines.Num())
		{
			float LineDuration = CurrentExchange->Lines[CurrentLineIndex].DisplayDuration;
			if (LineDisplayTime >= LineDuration)
			{
				// Move to next line or show choices
				CurrentLineIndex++;
				LineDisplayTime = 0.0f;

				if (CurrentLineIndex >= CurrentExchange->Lines.Num())
				{
					// All lines played, show choices
					PresentChoices();
				}
				else
				{
					// Play next line
					DisplayNextLine();
				}
			}
		}
	}
}

void ADialogueSystem::StartDialogueExchange(int32 ExchangeID)
{
	FDialogueExchange* Exchange = DialogueDatabase.Find(ExchangeID);
	if (!Exchange)
	{
		UE_LOG(LogTemp, Error, TEXT("Dialogue Exchange %d not found"), ExchangeID);
		return;
	}

	if (Exchange->bIsOneTime && Exchange->bHasBeenPlayed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue Exchange %d has already been played"), ExchangeID);
		return;
	}

	bDialogueActive = true;
	CurrentExchangeID = ExchangeID;
	CurrentLineIndex = 0;
	LineDisplayTime = 0.0f;
	Exchange->bHasBeenPlayed = true;

	PlayedDialogueExchanges.Add(ExchangeID);

	OnDialogueStarted.Broadcast(ExchangeID);

	// Display first line
	DisplayNextLine();

	UE_LOG(LogTemp, Warning, TEXT("Dialogue Exchange %d started with NPC: %s"), ExchangeID, *Exchange->ContextNPC);
}

void ADialogueSystem::PlayDialogueLine(const FDialogueLine& Line)
{
	OnLineDisplayed.Broadcast(Line.DialogueText);

	UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *Line.SpeakerName, *Line.DialogueText.ToString());

	// TODO: Play audio if path specified
	if (!Line.AudioPath.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("  Audio: %s"), *Line.AudioPath);
	}
}

void ADialogueSystem::EndDialogueExchange()
{
	if (!bDialogueActive)
	{
		return;
	}

	int32 ExchangeID = CurrentExchangeID;
	bDialogueActive = false;
	CurrentExchangeID = -1;
	CurrentLineIndex = 0;
	LineDisplayTime = 0.0f;

	OnDialogueEnded.Broadcast(ExchangeID);

	UE_LOG(LogTemp, Warning, TEXT("Dialogue Exchange %d ended"), ExchangeID);
}

void ADialogueSystem::SelectDialogueChoice(int32 ChoiceID)
{
	FDialogueExchange* CurrentExchange = DialogueDatabase.Find(CurrentExchangeID);
	if (!CurrentExchange)
	{
		return;
	}

	// Find chosen option
	FDialogueChoice* SelectedChoice = nullptr;
	for (FDialogueChoice& Choice : CurrentExchange->PlayerChoices)
	{
		if (Choice.ChoiceID == ChoiceID)
		{
			SelectedChoice = &Choice;
			break;
		}
	}

	if (!SelectedChoice)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Dialogue choice selected: %s (Moral Weight: %.2f)"), 
		   *SelectedChoice->ChoiceText.ToString(), SelectedChoice->MoralWeight);

	// Apply moral weight to player
	// TODO: Call GameMode->RecordMoralChoice()

	// Update relationship
	ModifyNPCRelationship(CurrentExchange->ContextNPC, SelectedChoice->MoralWeight);

	// Play next dialogue or end
	if (SelectedChoice->NextDialogueID > 0)
	{
		EndDialogueExchange();
		StartDialogueExchange(SelectedChoice->NextDialogueID);
	}
	else
	{
		EndDialogueExchange();
	}
}

void ADialogueSystem::ModifyNPCRelationship(const FString& NPCName, float RelationshipChange)
{
	float* CurrentRelationship = NPCRelationships.Find(NPCName);
	if (CurrentRelationship)
	{
		*CurrentRelationship += RelationshipChange;
		*CurrentRelationship = FMath::Clamp(*CurrentRelationship, -100.0f, 100.0f);

		UE_LOG(LogTemp, Warning, TEXT("NPC '%s' relationship now: %.1f"), *NPCName, *CurrentRelationship);
	}
}

float ADialogueSystem::GetNPCRelationship(const FString& NPCName) const
{
	const float* Relationship = NPCRelationships.Find(NPCName);
	return Relationship ? *Relationship : 0.0f;
}

void ADialogueSystem::RegisterDialogueExchange(const FDialogueExchange& Exchange)
{
	DialogueDatabase.Add(Exchange.ExchangeID, Exchange);

	UE_LOG(LogTemp, Warning, TEXT("Dialogue Exchange %d registered: %s (%d lines, %d choices)"), 
		   Exchange.ExchangeID, *Exchange.ContextNPC, Exchange.Lines.Num(), Exchange.PlayerChoices.Num());
}

void ADialogueSystem::DisplayNextLine()
{
	FDialogueExchange* CurrentExchange = DialogueDatabase.Find(CurrentExchangeID);
	if (!CurrentExchange || CurrentLineIndex >= CurrentExchange->Lines.Num())
	{
		return;
	}

	PlayDialogueLine(CurrentExchange->Lines[CurrentLineIndex]);
}

void ADialogueSystem::PresentChoices()
{
	FDialogueExchange* CurrentExchange = DialogueDatabase.Find(CurrentExchangeID);
	if (!CurrentExchange)
	{
		return;
	}

	OnChoicesPresented.Broadcast(CurrentExchange->PlayerChoices);

	UE_LOG(LogTemp, Warning, TEXT("Dialogue choices presented: %d options"), CurrentExchange->PlayerChoices.Num());
}
