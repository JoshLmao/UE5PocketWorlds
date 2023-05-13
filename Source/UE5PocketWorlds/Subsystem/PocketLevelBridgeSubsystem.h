

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <GameplayTagContainer.h>

#include "PocketLevelBridgeSubsystem.generated.h"

/**
 * A bridge subsystem to act as a connection between creating pocket worlds.
 * 
 * Ideally we would want this to inherit from `UPocketLevelSubsystem` from inside PocketWorlds plugin,
 * however we can't as it doesn't contain a ShouldCreateSubsystem override to disable creation if we derive one or more classes
 */
UCLASS()
class UE5POCKETWORLDS_API UPocketLevelBridgeSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	// Spawns the given pocket level
	void SpawnPocketLevel(class ULocalPlayer* OwningLocalPlayer, class UPocketLevel* PocketLevelDefintion, FVector SpawnLocation);

	// Gets the stage manager for the created pocket level
	class APocketLevelStageManager* GetStageManager(FGameplayTag PocketLevelGameplayTag);
};
