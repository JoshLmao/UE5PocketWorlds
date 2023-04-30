#include "UW_CharacterRepresentation.h"
#include "Components/Image.h"
#include "Materials/Material.h"

void UUW_CharacterRepresentation::NativePreConstruct()
{
	Super::NativePreConstruct();

	RenderImage->SetBrushFromMaterial(CameraRenderMaterial);
}
