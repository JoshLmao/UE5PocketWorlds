#include "InventoryRootWidgetActivatable.h"
#include "UE5PocketWorlds/UI/Foundation/FoundationBaseActivatable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(InventoryRootWidgetActivatable)

UInventoryRootWidgetActivatable::UInventoryRootWidgetActivatable()
{
	InputConfig = ELyraWidgetInputMode::Menu;
	GameMouseCaptureMode = EMouseCaptureMode::NoCapture;
}