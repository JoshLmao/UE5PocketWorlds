#include "PocketLevelBridgeSubsystem.h"
#include "PocketLevelSystem.h"
#include "PocketLevel.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "UE5PocketWorlds/Worlds/IdentifyingPocketLevel.h"
#include "PocketLevelInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UE5PocketWorlds/Worlds/PocketLevelStageManager.h"

void UPocketLevelBridgeSubsystem::SpawnPocketLevel(ULocalPlayer* OwningLocalPlayer, UIdentifyingPocketLevel* PocketLevelDefinition, FVector SpawnLocation)
{
	auto* pocketLevelInstance = GetWorld()->GetSubsystem<UPocketLevelSubsystem>()->GetOrCreatePocketLevelFor(OwningLocalPlayer, PocketLevelDefinition, SpawnLocation);

	SpawnedLevelsMap.Add(PocketLevelDefinition->IdentifingGameplayTag, pocketLevelInstance);
}

void UPocketLevelBridgeSubsystem::StreamInLevel(FGameplayTag PocketLevelGameplayTag)
{
	if (auto pocketlevelInstance = SpawnedLevelsMap.FindChecked(PocketLevelGameplayTag))
	{
		pocketlevelInstance->StreamIn();
	}
}

void UPocketLevelBridgeSubsystem::StreamOutLevel(FGameplayTag PocketLevelGameplayTag)
{
	if (auto* pocketlevelInstance = SpawnedLevelsMap.FindChecked(PocketLevelGameplayTag))
	{
		pocketlevelInstance->StreamOut();
	}
}

APocketLevelStageManager* UPocketLevelBridgeSubsystem::GetStageManager(FGameplayTag PocketLevelGameplayTag)
{
	auto* pocketlevelInstance = GetPocketLevelInstance(PocketLevelGameplayTag);

	// @todo improvement
	// Able to get streaming level from pocketlevelInstance and get spawned manager actor from that
	TArray<AActor*> outStageManagerActors;
	UGameplayStatics::GetAllActorsOfClass(pocketlevelInstance->GetWorld(), APocketLevelStageManager::StaticClass(), outStageManagerActors);
	for (auto stageManagerActor : outStageManagerActors)
	{
		if (auto stageManager = Cast<APocketLevelStageManager>(stageManagerActor))
		{
			if (stageManager->IdentifyingGameplayTag.MatchesTag(PocketLevelGameplayTag))
			{
				return stageManager;
			}
		}
	}

	return nullptr;
}

UPocketLevelInstance* UPocketLevelBridgeSubsystem::GetPocketLevelInstance(FGameplayTag PocketLevelGameplayTag)
{
	return SpawnedLevelsMap.FindChecked(PocketLevelGameplayTag);
}
