#include "PocketLevelBridgeSubsystem.h"
#include "PocketLevelSystem.h"
#include "PocketLevel.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "UE5PocketWorlds/Worlds/IdentifyingPocketLevel.h"
#include "PocketLevelInstance.h"

void UPocketLevelBridgeSubsystem::SpawnPocketLevel(ULocalPlayer* OwningLocalPlayer, UIdentifyingPocketLevel* PocketLevelDefinition, FVector SpawnLocation)
{
	auto* pocketLevelInstance = GetWorld()->GetSubsystem<UPocketLevelSubsystem>()->GetOrCreatePocketLevelFor(OwningLocalPlayer, PocketLevelDefinition, SpawnLocation);
	pocketLevelInstance->StreamOut();

	SpawnedLevelsMap.Add(PocketLevelDefinition->IdentifingGameplayTag, pocketLevelInstance);
}

APocketLevelStageManager* UPocketLevelBridgeSubsystem::GetStageManager(FGameplayTag PocketLevelGameplayTag)
{
	auto* levelInstance = SpawnedLevelsMap.FindChecked(PocketLevelGameplayTag);
	// @todo get stage manager from level instance
	return nullptr;
}
