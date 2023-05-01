#include "UW_CharacterRepresentation.h"
#include "Components/Image.h"
#include "Materials/Material.h"
#include "PocketLevelSystem.h"
#include "PocketLevelInstance.h"
#include "PocketCapture.h"
#include "Kismet/GameplayStatics.h"
#include "UE5PocketWorlds/Worlds/PocketLevelStageManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"

void UUW_CharacterRepresentation::NativePreConstruct()
{
	Super::NativePreConstruct();

	RenderImage->SetBrushFromMaterial(CameraRenderMaterial);
}

void UUW_CharacterRepresentation::NativeConstruct()
{
	Super::Construct();

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
	auto* pocketLevelStageManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), APocketLevelStageManager::StaticClass());
	if (auto stageManager = Cast<APocketLevelStageManager>(pocketLevelStageManagerActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Found Stage Manager!"));
		auto* sceneCapture = stageManager->GetPocketCapture();
		
		// Set Diffuse and AlphaMask for dynamic material of the image
		auto* imageMaterial = RenderImage->GetDynamicMaterial();
		imageMaterial->SetTextureParameterValue(TEXT("Diffuse"), sceneCapture->GetOrCreateDiffuseRenderTarget());
		imageMaterial->SetTextureParameterValue(TEXT("AlphaMask"), sceneCapture->GetOrCreateAlphaMaskRenderTarget());

		// capture one frame for now
		// @todo do every tick
		sceneCapture->CaptureDiffuse();
	}
}