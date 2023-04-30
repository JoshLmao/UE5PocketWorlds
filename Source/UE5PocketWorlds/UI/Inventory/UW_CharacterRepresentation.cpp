#include "UW_CharacterRepresentation.h"
#include "Components/Image.h"
#include "Materials/Material.h"
#include "PocketLevelSystem.h"
#include "PocketLevelInstance.h"
#include "PocketCaptureSubsystem.h"

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

	auto* pocketCaptureSubsys = GetWorld()->GetSubsystem<UPocketCaptureSubsystem>();
	PocketCaptureInstance = pocketCaptureSubsys->CreateThumbnailRenderer(PocketCaptureClass);
	check(PocketCaptureInstance != nullptr);

	PocketLevelInstance->StreamIn();
}