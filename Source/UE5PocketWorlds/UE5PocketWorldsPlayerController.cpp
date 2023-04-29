#include "UE5PocketWorldsPlayerController.h"
#include "Component/PlayerInventoryComponent.h"
#include "CommonLocalPlayer.h"
#include "CommonUIExtensions.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

AUE5PocketWorldsPlayerController::AUE5PocketWorldsPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> CustomRootInventoryWidget(TEXT("/Game/PocketWorlds/UI/InGame/WBP_PlayerHUDLayout"));
	PlayerHUDWidgetClass = CustomRootInventoryWidget.Class;

	InventoryComponent = CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("Player Inventory Component"));
}

void AUE5PocketWorldsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UCommonUIExtensions::PushContentToLayer_ForPlayer(GetLocalPlayer(), FGameplayTag::RequestGameplayTag("UI.Layer.Game"), PlayerHUDWidgetClass);
}

void AUE5PocketWorldsPlayerController::ToggleInventory(bool open)
{
	InventoryComponent->ToggleOpen(open);
}

void AUE5PocketWorldsPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	// Scaffolding from Lyra
	if (UCommonLocalPlayer* LocalPlayer = Cast<UCommonLocalPlayer>(Player))
	{
		LocalPlayer->OnPlayerControllerSet.Broadcast(LocalPlayer, this);

		if (PlayerState)
		{
			LocalPlayer->OnPlayerStateSet.Broadcast(LocalPlayer, PlayerState);
		}
	}
}
