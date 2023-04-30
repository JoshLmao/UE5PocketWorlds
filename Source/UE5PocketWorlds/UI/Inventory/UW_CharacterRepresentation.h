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

protected:
	// Material the world camera paints to
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* CameraRenderMaterial;
};
