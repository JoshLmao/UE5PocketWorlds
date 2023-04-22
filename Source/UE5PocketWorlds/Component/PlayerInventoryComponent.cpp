
#include "PlayerInventoryComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	// todo: make root widget and specify WBP here
	//static ConstructorHelpers::FClassFinder<UUserWidget> CustomRootInventoryWidget(TEXT("/Game/UI/Inventory/...."));
	//InventoryRootWidget = CustomRootInventoryWidget.Class;
}

void UPlayerInventoryComponent::ToggleOpen(bool isOpen)
{
	return;
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
