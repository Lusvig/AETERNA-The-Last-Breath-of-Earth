#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryEchoSystem.generated.h"

// Memory Echo structure
USTRUCT(BlueprintType)
struct FMemoryEcho
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	int32 EchoID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	FString NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	FString EchoTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	FString EchoDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	float DurationSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	FVector EchoLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	bool bHasBeenTriggered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	FString CinematicSequencePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
	int32 MoralWeight; // How much this echo affects ending calculation

	FMemoryEcho()
		: EchoID(0), NPCName(TEXT("")), EchoTitle(TEXT("")), EchoDescription(TEXT("")),
		  DurationSeconds(0.0f), EchoLocation(FVector::ZeroVector), bHasBeenTriggered(false),
		  CinematicSequencePath(TEXT("")), MoralWeight(1)
	{
	}
};

/**
 * AMemoryEchoSystem
 * Manages all Memory Echo narratives and triggering
 */
UCLASS()
class AETERNA_API AMemoryEchoSystem : public AActor
{
	GENERATED_BODY()

public:
	AMemoryEchoSystem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Register a new echo
	UFUNCTION(BlueprintCallable, Category = "Memory Echo")
	void RegisterEcho(const FMemoryEcho& NewEcho);

	// Trigger an echo playback
	UFUNCTION(BlueprintCallable, Category = "Memory Echo")
	void TriggerEcho(int32 EchoID);

	// Get echo by ID
	UFUNCTION(BlueprintCallable, Category = "Memory Echo")
	FMemoryEcho GetEcho(int32 EchoID);

	// Get all echoes
	UFUNCTION(BlueprintCallable, Category = "Memory Echo")
	TArray<FMemoryEcho> GetAllEchoes() const { return AllEchoes; }

	// Get triggered echoes
	UFUNCTION(BlueprintCallable, Category = "Memory Echo")
	TArray<FMemoryEcho> GetTriggeredEchoes() const;

	// Check if echo has been seen
	UFUNCTION(BlueprintCallable, Category = "Memory Echo")
	bool HasEchoBeenTriggered(int32 EchoID) const;

	// Mark echo as triggered
	UFUNCTION(BlueprintCallable, Category = "Memory Echo")
	void MarkEchoTriggered(int32 EchoID);

	// Events
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEchoTriggered, int32);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEchoCompleted, int32);

	FOnEchoTriggered OnEchoTriggered;
	FOnEchoCompleted OnEchoCompleted;

protected:
	// All registered echoes
	UPROPERTY()
	TArray<FMemoryEcho> AllEchoes;

	// Currently playing echo
	UPROPERTY()
	int32 CurrentlyPlayingEchoID;

	UPROPERTY()
	float EchoPlaybackTime;

private:
	void InitializeDefaultEchoes();
};
