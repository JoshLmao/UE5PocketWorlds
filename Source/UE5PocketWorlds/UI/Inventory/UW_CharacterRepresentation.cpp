#include "UW_CharacterRepresentation.h"
#include "Components/Image.h"
#include "Materials/Material.h"
#include "PocketLevelSystem.h"
#include "PocketLevelInstance.h"
#include "PocketCapture.h"
#include "UE5PocketWorlds/Worlds/PocketLevelStageManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UE5PocketWorlds/Subsystem/PocketLevelBridgeSubsystem.h"

void UUW_CharacterRepresentation::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (RenderImage != nullptr)
	{
		RenderImage->SetBrushFromMaterial(CameraRenderMaterial);	
	}
}

void UUW_CharacterRepresentation::NativeConstruct()
{
	Super::NativeConstruct();

	// Obtain pocket level instance for inventory
	auto bridgeSubsys = GetWorld()->GetSubsystem<UPocketLevelBridgeSubsystem>();
	auto* inventoryLevelInstance = bridgeSubsys->GetPocketLevelInstance(InventoryPocketWorldGameplayTag);
	
	// Add callback to when streamed in level is ready
	auto delegate = FPocketLevelInstanceEvent::FDelegate::CreateUObject(this, &UUW_CharacterRepresentation::OnInventoryLevelReady);
	PocketLevelReadyDelegateHandle = inventoryLevelInstance->AddReadyCallback(delegate);
	
	// Begin stream in process
	inventoryLevelInstance->StreamIn();
}

void UUW_CharacterRepresentation::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CaptureFrame();
}

void UUW_CharacterRepresentation::NativeDestruct()
{
	Super::NativeDestruct();

	// Obtain pocket level instance for inventory
	auto bridgeSubsys = GetWorld()->GetSubsystem<UPocketLevelBridgeSubsystem>();
	auto* inventoryLevelInstance = bridgeSubsys->GetPocketLevelInstance(InventoryPocketWorldGameplayTag);

	// Stop listening to ready callback, stream out the level
	inventoryLevelInstance->RemoveReadyCallback(PocketLevelReadyDelegateHandle);
	inventoryLevelInstance->StreamOut();
}

void UUW_CharacterRepresentation::CaptureFrame()
{
	// When valid, capture every frame of the capture instance
	if (PocketCaptureInstance != nullptr)
	{
		PocketCaptureInstance->CaptureDiffuse();
		PocketCaptureInstance->CaptureAlphaMask();
	}
}

void UUW_CharacterRepresentation::OnInventoryLevelReady(UPocketLevelInstance* Instance)
{
	auto bridgeSubsys = GetWorld()->GetSubsystem<UPocketLevelBridgeSubsystem>();
	
	// Get stage manager for the instance
	APocketLevelStageManager* pocketLevelStageManager = bridgeSubsys->GetStageManager(InventoryPocketWorldGameplayTag);
	check(pocketLevelStageManager != nullptr && "Unable to find pocket world stage manager");

	// Obtain pocket capture of stage
	PocketCaptureInstance = pocketLevelStageManager->GetPocketCapture();

	// Set Diffuse and AlphaMask for dynamic material of the image
	auto* imageMaterial = RenderImage->GetDynamicMaterial();
	imageMaterial->SetTextureParameterValue(TEXT("Diffuse"), PocketCaptureInstance->GetOrCreateDiffuseRenderTarget());
	imageMaterial->SetTextureParameterValue(TEXT("AlphaMask"), PocketCaptureInstance->GetOrCreateAlphaMaskRenderTarget());
}
