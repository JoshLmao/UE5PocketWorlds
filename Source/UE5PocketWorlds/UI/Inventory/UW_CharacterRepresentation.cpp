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

	// @todo: reliably access spawned pocket level world to get manager
	auto bridgeSubsys = GetWorld()->GetSubsystem<UPocketLevelBridgeSubsystem>();
	APocketLevelStageManager* pocketLevelStageManager = bridgeSubsys->GetStageManager(InventoryPocketWorldGameplayTag);
	
	check(pocketLevelStageManager != nullptr && "Unable to find pocket world stage manager");
	PocketCaptureInstance = pocketLevelStageManager->GetPocketCapture();

	// Set Diffuse and AlphaMask for dynamic material of the image
	auto* imageMaterial = RenderImage->GetDynamicMaterial();
	imageMaterial->SetTextureParameterValue(TEXT("Diffuse"), PocketCaptureInstance->GetOrCreateDiffuseRenderTarget());
	imageMaterial->SetTextureParameterValue(TEXT("AlphaMask"), PocketCaptureInstance->GetOrCreateAlphaMaskRenderTarget());
}

void UUW_CharacterRepresentation::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CaptureFrame();
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
