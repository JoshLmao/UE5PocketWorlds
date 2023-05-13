#include "PocketLevelBridgeSubsystem.h"
#include "PocketLevelSystem.h"
#include "PocketLevel.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"

void UPocketLevelBridgeSubsystem::SpawnPocketLevel(ULocalPlayer* OwningLocalPlayer, UPocketLevel* PocketLevelDefinition, FVector SpawnLocation)
{
	auto* pocketLvlInstance = GetWorld()->GetSubsystem<UPocketLevelSubsystem>()->GetOrCreatePocketLevelFor(OwningLocalPlayer, PocketLevelDefinition, SpawnLocation);
}

APocketLevelStageManager* UPocketLevelBridgeSubsystem::GetStageManager(FGameplayTag PocketLevelGameplayTag)
{
	return nullptr;	//@todo
}
