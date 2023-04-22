
#include "PlayerInventoryComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> CustomRootInventoryWidget(TEXT("/Game/PocketWorlds/UI/Inventory/WBP_InventoryRootWidget"));
	InventoryRootWidget = CustomRootInventoryWidget.Class;
}

void UPlayerInventoryComponent::ToggleOpen(bool isOpen)
{
	if (isOpen)
	{
		CreatedRoot = CreateWidget<UUserWidget>(GetWorld(), InventoryRootWidget);
		CreatedRoot->AddToViewport();
	}
	else
	{
		if (CreatedRoot != nullptr)
		{
			// todo: cast inst. widget to root type and call Close()
		}
	}
}
