#include "PlayerInventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "PrimaryGameLayout.h"
#include "GameFramework/PlayerController.h"
#include <UE5PocketWorlds/Player/PocketWorldsLocalPlayer.h>
#include "CommonActivatableWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5PocketWorlds/UI/Foundation/FoundationBaseActivatable.h"
#include "UE5PocketWorlds/UE5PocketWorlds.h"

// Sets default values for this component's properties
UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	static ConstructorHelpers::FClassFinder<UFoundationBaseActivatable> CustomRootInventoryWidget(TEXT("/Game/PocketWorlds/UI/Inventory/WBP_InventoryRoot_Activatable"));
	if (CustomRootInventoryWidget.Class != NULL)
	{
		InventoryRootWidget = CustomRootInventoryWidget.Class;
	}
}

void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayerController = Cast<APlayerController>(GetOwner());
}

bool UPlayerInventoryComponent::Open()
{
	if (CreatedRoot != nullptr)
	{
		return false;
	}

	if (auto* localPlayer = Cast<UPocketWorldsLocalPlayer>(OwningPlayerController->GetLocalPlayer()))
	{
		if (auto* primaryLayout = localPlayer->GetRootUILayout())
		{
			auto layer = FGameplayTag::RequestGameplayTag("UI.Layer.GameMenu");
			CreatedRoot = primaryLayout->PushWidgetToLayerStack<UFoundationBaseActivatable>(layer, InventoryRootWidget, [](UFoundationBaseActivatable& Activatable) {
				UE_LOG(LogUIDebug, Log, TEXT("Inventory: Opened"));
			});
			InventoryDeactivatedHandle = CreatedRoot->OnDeactivated().AddUObject(this, &UPlayerInventoryComponent::OnInventoryClosed);
			return true;
		}
	}
	return false;
}

void UPlayerInventoryComponent::OnInventoryClosed()
{
	UE_LOG(LogUIDebug, Log, TEXT("Inventory: Closed"));
	CreatedRoot->OnDeactivated().Remove(InventoryDeactivatedHandle);
	CreatedRoot = nullptr;
}