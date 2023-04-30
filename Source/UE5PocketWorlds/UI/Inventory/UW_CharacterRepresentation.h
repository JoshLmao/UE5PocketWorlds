#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UW_CharacterRepresentation.generated.h"

/**
 * Widget that paints a material of a render texture to a UserWidget Image
 */
UCLASS()
class UE5POCKETWORLDS_API UUW_CharacterRepresentation : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UImage* RenderImage;

	void NativePreConstruct() override;
	void NativeConstruct() override;

protected:
	// Material the world camera paints to
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* CameraRenderMaterial;

	// Data asset that defines our pocket level to use
	UPROPERTY(EditDefaultsOnly)
	class UPocketLevel* InventoryPocketLevelDefinition;

	// Location in current level to spawn our pocket level
	UPROPERTY(EditDefaultsOnly)
	FVector PocketLevelSpawnLocation = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPocketCapture> PocketCaptureClass;

private:
	// Our created level instance
	class UPocketLevelInstance* PocketLevelInstance;
	class UPocketCapture* PocketCaptureInstance;

	UFUNCTION()
	void OnLevelReady(UPocketLevelInstance* Instance);
};
