

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PocketLevelStageManager.generated.h"

/*
* Actor to control and manage a Pocket World level
*/
UCLASS()
class UE5POCKETWORLDS_API APocketLevelStageManager : public AActor
{
	GENERATED_BODY()

public:
	APocketLevelStageManager();

protected:
	void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ActorToSpawn;

	// Component to act as root as where to spawn actors from
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* ActorSpawnPointComponent;

	// Config for PocketCapture
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPocketCapture> PocketCaptureClass;

	// Active pocket capture instance for this pocket level
	class UPocketCapture* PocketCaptureInst;
	class AActor* SpawnedActor;

	// Gets the active UPocketCapture instance for this PocketLevel
	UFUNCTION(BlueprintCallable)
	UPocketCapture* GetPocketCapture();
};