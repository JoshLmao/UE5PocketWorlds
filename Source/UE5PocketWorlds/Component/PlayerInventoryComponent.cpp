#include "PlayerInventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "CommonActivatableWidget.h"
#include "GameFramework/PlayerController.h"
#include "PrimaryGameLayout.h"
#include "UE5PocketWorlds/UE5PocketWorlds.h"
#include "UE5PocketWorlds/UI/Foundation/FoundationBaseActivatable.h"
#include "UObject/ConstructorHelpers.h"
#include <UE5PocketWorlds/Player/PocketWorldsLocalPlayer.h>

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

	if (const auto* LocalPlayer = Cast<UPocketWorldsLocalPlayer>(OwningPlayerController->GetLocalPlayer()))
	{
		if (auto* PrimaryGameLayout = LocalPlayer->GetRootUILayout())
		{
			const auto Layer = FGameplayTag::RequestGameplayTag("UI.Layer.GameMenu");
			CreatedRoot = PrimaryGameLayout->PushWidgetToLayerStack<UFoundationBaseActivatable>(Layer, InventoryRootWidget, [](UFoundationBaseActivatable& Activatable)
																								{ UE_LOG(LogUIDebug, Log, TEXT("Inventory: Opened")); });
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