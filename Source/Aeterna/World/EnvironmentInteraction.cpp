#include "EnvironmentInteraction.h"
#include "Kismet/GameplayStatics.h"

AEnvironmentInteraction::AEnvironmentInteraction()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.2f;

	bIsInteractable = true;
	InteractionType = EInteractableType::Collectible;
	InteractionPrompt = FText::FromString(TEXT("Examine"));
	InteractionRange = 200.0f;
	bShowOutlineWhenNear = true;
	OutlineColor = FLinearColor::Yellow;

	DistanceToPlayer = 0.0f;
	bPlayerInRange = false;
}

void AEnvironmentInteraction::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Environment interaction placed: %s (Type: %d)"), *GetName(), (int32)InteractionType);
}

void AEnvironmentInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update distance to player for feedback
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());
		bool bNewInRange = DistanceToPlayer < InteractionRange && bIsInteractable;

		if (bNewInRange && !bPlayerInRange)
		{
			// Player entered range
			bPlayerInRange = true;
			// TODO: Show interaction prompt
		}
		else if (!bNewInRange && bPlayerInRange)
		{
			// Player left range
			bPlayerInRange = false;
			// TODO: Hide interaction prompt
		}
	}
}

void AEnvironmentInteraction::OnInteract_Implementation(APawn* Interactor)
{
	if (!bIsInteractable)
	{
		return;
	}

	OnInteracted.Broadcast(Interactor);

	UE_LOG(LogTemp, Warning, TEXT("Interaction triggered: %s by %s"), *GetName(), *Interactor->GetName());
}

void AEnvironmentInteraction::SetInteractable(bool bNewInteractable)
{
	bIsInteractable = bNewInteractable;
}
