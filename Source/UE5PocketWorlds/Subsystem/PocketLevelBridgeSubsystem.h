

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
	void SpawnPocketLevel(class ULocalPlayer* OwningLocalPlayer, class UIdentifyingPocketLevel* PocketLevelDefintion, const FVector& SpawnLocation);

	void StreamInLevel(const struct FGameplayTag& LevelIdentifier);
	void StreamOutLevel(const struct FGameplayTag& LevelIdentifier);

	// Gets the stage manager for the created pocket level
	class APocketLevelStageManager* GetStageManager(const struct FGameplayTag& PocketLevelGameplayTag);
	// Gets the PocketLevelInstance for the created pocket level
	class UPocketLevelInstance* GetPocketLevelInstance(const struct FGameplayTag& PocketLevelGameplayTag);

private:
	// Cache of identifying gameplay tag to created pocket world instances
	TMap<FGameplayTag, class UPocketLevelInstance*> SpawnedLevelsMap;
};
