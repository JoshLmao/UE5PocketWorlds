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
	const auto PocketLevelBridgeSubsystem = GetWorld()->GetSubsystem<UPocketLevelBridgeSubsystem>();
	auto* InventoryLevelInstance = PocketLevelBridgeSubsystem->GetPocketLevelInstance(InventoryPocketWorldGameplayTag);
	
	// Add callback to when streamed in level is ready
	const auto ReadyDelegate = FPocketLevelInstanceEvent::FDelegate::CreateUObject(this, &UUW_CharacterRepresentation::OnInventoryLevelReady);
	PocketLevelReadyDelegateHandle = InventoryLevelInstance->AddReadyCallback(ReadyDelegate);
	
	// Begin stream in process
	InventoryLevelInstance->StreamIn();
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
	auto PocketLevelBridgeSubsystem = GetWorld()->GetSubsystem<UPocketLevelBridgeSubsystem>();
	auto* InventoryLevelInstance = PocketLevelBridgeSubsystem->GetPocketLevelInstance(InventoryPocketWorldGameplayTag);

	// Stop listening to ready callback, stream out the level
	InventoryLevelInstance->RemoveReadyCallback(PocketLevelReadyDelegateHandle);
	InventoryLevelInstance->StreamOut();
}

void UUW_CharacterRepresentation::CaptureFrame() const
{
	// Capture every frame of the pocket world capture instance
	if (IsValid(PocketCaptureInstance))
	{
		PocketCaptureInstance->CaptureDiffuse();
		PocketCaptureInstance->CaptureAlphaMask();
	}
}

void UUW_CharacterRepresentation::OnInventoryLevelReady(UPocketLevelInstance* Instance)
{
	const auto PocketLevelBridgeSubsystem = GetWorld()->GetSubsystem<UPocketLevelBridgeSubsystem>();
	
	// Get stage manager for the instance
	APocketLevelStageManager* PocketLevelStageManager = PocketLevelBridgeSubsystem->GetStageManager(InventoryPocketWorldGameplayTag);
	check(PocketLevelStageManager != nullptr && "Unable to find pocket world stage manager");

	// Obtain pocket capture of stage
	PocketCaptureInstance = PocketLevelStageManager->GetPocketCapture();

	// Set Diffuse and AlphaMask for dynamic material of the image
	auto* ImgMaterial = RenderImage->GetDynamicMaterial();
	ImgMaterial->SetTextureParameterValue(TEXT("Diffuse"), PocketCaptureInstance->GetOrCreateDiffuseRenderTarget());
	ImgMaterial->SetTextureParameterValue(TEXT("AlphaMask"), PocketCaptureInstance->GetOrCreateAlphaMaskRenderTarget());
}
