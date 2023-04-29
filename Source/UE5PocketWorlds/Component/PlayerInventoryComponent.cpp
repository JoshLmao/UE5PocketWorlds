
#include "PlayerInventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "PrimaryGameLayout.h"
#include "GameFramework/PlayerController.h"
#include <UE5PocketWorlds/Player/PocketWorldsLocalPlayer.h>
#include "CommonActivatableWidget.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> CustomRootInventoryWidget(TEXT("/Game/PocketWorlds/UI/Inventory/WBP_InventoryRoot_Activatable"));
	InventoryRootWidget = CustomRootInventoryWidget.Class;
}

void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayerController = Cast<APlayerController>(GetOwner());
}

void UPlayerInventoryComponent::ToggleOpen(bool isOpen)
{
	if (isOpen)
	{
		if (auto* localPlayer = Cast<UPocketWorldsLocalPlayer>(OwningPlayerController->GetLocalPlayer()))
		{
			if (auto* primaryLayout = localPlayer->GetRootUILayout())
			{
				auto layer = FGameplayTag::RequestGameplayTag("UI.Layer.GameMenu");
				primaryLayout->PushWidgetToLayerStack<UCommonActivatableWidget>(layer, InventoryRootWidget, [](UCommonActivatableWidget& Activatable) {
					UE_LOG(LogTemp, Log, TEXT("Activatable pushed to screen"));
				});
			}
		}
	}
	else
	{
		if (CreatedRoot != nullptr)
		{
			// todo: cast inst. widget to root type and call Close()
		}
	}
}

