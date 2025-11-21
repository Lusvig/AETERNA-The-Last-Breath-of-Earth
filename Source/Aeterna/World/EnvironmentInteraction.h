#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvironmentInteraction.generated.h"

// Interactable object types
UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	Collectible = 0		UMETA(DisplayName = "Collectible"),
	Container = 1		UMETA(DisplayName = "Container"),
	Environmental = 2	UMETA(DisplayName = "Environmental Hazard"),
	Narrative = 3		UMETA(DisplayName = "Story Trigger"),
	Creature = 4		UMETA(DisplayName = "Creature")
};

/**
 * AEnvironmentInteraction
 * Base class for all interactive objects in the world
 */
UCLASS()
class AETERNA_API AEnvironmentInteraction : public AActor
{
	GENERATED_BODY()

public:
	AEnvironmentInteraction();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Interaction interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Interaction")
	void OnInteract(APawn* Interactor);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractable(bool bNewInteractable);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool IsInteractable() const { return bIsInteractable; }

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	EInteractableType GetInteractionType() const { return InteractionType; }

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FText GetInteractionPrompt() const { return InteractionPrompt; }

	// Events
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteracted, APawn*);
	FOnInteracted OnInteracted;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsInteractable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	EInteractableType InteractionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractionPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionRange;

	// Visual feedback
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	bool bShowOutlineWhenNear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	FLinearColor OutlineColor;

private:
	float DistanceToPlayer;
	bool bPlayerInRange;
};
