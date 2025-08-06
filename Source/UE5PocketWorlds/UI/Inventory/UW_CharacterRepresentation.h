#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "UW_CharacterRepresentation.generated.h"

/**
 * Widget that paints a material of a render texture to a UserWidget Image
 */
UCLASS()
class UE5POCKETWORLDS_API UUW_CharacterRepresentation : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	// Image element to render pocket capture to
	UPROPERTY(meta = (BindWidget))
	class UImage* RenderImage;

	void NativePreConstruct() override;
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void NativeDestruct() override;

protected:
	// Material the world camera paints to
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* CameraRenderMaterial;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InventoryPocketWorldGameplayTag;

private:
	// Capture instance
	UPROPERTY()
	class UPocketCapture* PocketCaptureInstance;

	void CaptureFrame() const;

	UFUNCTION()
	void OnInventoryLevelReady(class UPocketLevelInstance* Instance);

	FDelegateHandle PocketLevelReadyDelegateHandle;
};
