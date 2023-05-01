

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
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
	// Config for PocketCapture
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPocketCapture> PocketCaptureClass;

	// Active pocket capture instance for this pocket level
	class UPocketCapture* PocketCaptureInst;

	// Gets the active UPocketCapture instance for this PocketLevel
	UFUNCTION(BlueprintCallable)
	UPocketCapture* GetPocketCapture();

	// Spawns a given actor in the pocket level
	AActor* SpawnActorInPocketLevel(TSubclassOf<AActor> ActorClassToSpawn, FActorSpawnParameters ActorSpawnParams);

private:
	// Custom root component, scene component
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* RootSceneComponent;

	// Component to act as root as where to spawn actors from
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* ActorSpawnPointComponent;

	// @todo
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
};