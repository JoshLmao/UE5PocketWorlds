#include "PocketLevelBridgeSubsystem.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "PocketLevel.h"
#include "PocketLevelInstance.h"
#include "PocketLevelSystem.h"
#include "UE5PocketWorlds/Worlds/IdentifyingPocketLevel.h"
#include "UE5PocketWorlds/Worlds/PocketLevelStageManager.h"

void UPocketLevelBridgeSubsystem::SpawnPocketLevel(ULocalPlayer* OwningLocalPlayer, UIdentifyingPocketLevel* PocketLevelDefinition, const FVector& SpawnLocation)
{
	auto* PocketLevelInstance = GetWorld()->GetSubsystem<UPocketLevelSubsystem>()->GetOrCreatePocketLevelFor(OwningLocalPlayer, PocketLevelDefinition, SpawnLocation);
	SpawnedLevelsMap.Add(PocketLevelDefinition->IdentifingGameplayTag, PocketLevelInstance);
}

void UPocketLevelBridgeSubsystem::StreamInLevel(const FGameplayTag& PocketLevelGameplayTag)
{
	if (auto PocketLevelInstance = SpawnedLevelsMap.FindChecked(PocketLevelGameplayTag))
	{
		PocketLevelInstance->StreamIn();
	}
}

void UPocketLevelBridgeSubsystem::StreamOutLevel(const FGameplayTag& PocketLevelGameplayTag)
{
	if (auto* pocketlevelInstance = SpawnedLevelsMap.FindChecked(PocketLevelGameplayTag))
	{
		pocketlevelInstance->StreamOut();
	}
}

APocketLevelStageManager* UPocketLevelBridgeSubsystem::GetStageManager(const FGameplayTag& PocketLevelGameplayTag)
{
	const auto* PocketLevelInstance = GetPocketLevelInstance(PocketLevelGameplayTag);

	// @todo improvement
	// Able to get streaming level from PocketLevelInstance and get spawned manager actor from that
	TArray<AActor*> OutStageManagerActors;
	UGameplayStatics::GetAllActorsOfClass(PocketLevelInstance->GetWorld(), APocketLevelStageManager::StaticClass(), OutStageManagerActors);
	for (auto StageManagerActor : OutStageManagerActors)

	{
		if (auto StageManager = Cast<APocketLevelStageManager>(StageManagerActor))
		{
			if (StageManager->IdentifyingGameplayTag.MatchesTag(PocketLevelGameplayTag))
			{
				return StageManager;
			}
		}
	}

	return nullptr;
}

UPocketLevelInstance* UPocketLevelBridgeSubsystem::GetPocketLevelInstance(const FGameplayTag& PocketLevelGameplayTag)
{
	return SpawnedLevelsMap.FindChecked(PocketLevelGameplayTag);
}
