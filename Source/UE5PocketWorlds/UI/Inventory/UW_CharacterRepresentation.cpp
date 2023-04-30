#include "UW_CharacterRepresentation.h"
#include "Components/Image.h"
#include "Materials/Material.h"
#include "PocketLevelSystem.h"
#include "PocketLevelInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UE5PocketWorlds/Worlds/PocketLevelStageManager.h"

void UUW_CharacterRepresentation::NativePreConstruct()
{
	Super::NativePreConstruct();

	RenderImage->SetBrushFromMaterial(CameraRenderMaterial);
}

void UUW_CharacterRepresentation::NativeConstruct()
{
	// Get subsystem that controls creating/loading pocket world levels
	auto* pocketLevelSubsys = GetWorld()->GetSubsystem<UPocketLevelSubsystem>();
	// Create our defined level
	PocketLevelInstance = pocketLevelSubsys->GetOrCreatePocketLevelFor(GetOwningLocalPlayer(), InventoryPocketLevelDefinition, PocketLevelSpawnLocation);
	check(PocketLevelInstance != nullptr && "You need to define a valid level definition");

	auto readyDelegate = FPocketLevelInstanceEvent::FDelegate::CreateUObject(this, &UUW_CharacterRepresentation::OnLevelReady);
	PocketLevelInstance->AddReadyCallback(readyDelegate);
}

void UUW_CharacterRepresentation::OnLevelReady(UPocketLevelInstance* Instance)
{
	// @todo: reliably access spawned pocket level world to get manager
	auto* pocketLevelStageManager = UGameplayStatics::GetActorOfClass(GetWorld(), APocketLevelStageManager::StaticClass());
	if (pocketLevelStageManager != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Found Stage Manager!"));
	}
}