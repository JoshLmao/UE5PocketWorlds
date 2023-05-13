#include "UE5PocketWorldsPlayerController.h"
#include "Component/PlayerInventoryComponent.h"
#include "CommonLocalPlayer.h"
#include "CommonUIExtensions.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UE5PocketWorlds/UI/Foundation/FoundationBaseActivatable.h"
#include "Subsystem/PocketLevelBridgeSubsystem.h"
#include "GameFramework/Character.h"
#include "UE5PocketWorlds/Worlds/IdentifyingPocketLevel.h"

AUE5PocketWorldsPlayerController::AUE5PocketWorldsPlayerController()
{
	static ConstructorHelpers::FClassFinder<UFoundationBaseActivatable> CustomRootInventoryWidget(
		TEXT("/Game/PocketWorlds/UI/InGame/WBP_PlayerHUDLayout")
	);
	PlayerHUDWidgetClass = CustomRootInventoryWidget.Class;

	InventoryComponent = CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("Player Inventory Component"));
}

void AUE5PocketWorldsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Push Player HUD to screen
	UCommonUIExtensions::PushContentToLayer_ForPlayer(GetLocalPlayer(), FGameplayTag::RequestGameplayTag("UI.Layer.Game"), PlayerHUDWidgetClass);

	InitInventoryPocketWorld();
}

void AUE5PocketWorldsPlayerController::ToggleInventory(bool open)
{
	if (open) 
	{
		InventoryComponent->Open();
	}
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

void AUE5PocketWorldsPlayerController::InitInventoryPocketWorld()
{
	if (InventoryPocketLevelDefinition != nullptr)
	{
		// Get subsystem that controls creating/loading pocket world levels
		auto* bridgeSubsystem = GetWorld()->GetSubsystem<UPocketLevelBridgeSubsystem>();

		// Spawn defined level and StreamOut until we're ready to use it
		bridgeSubsystem->SpawnPocketLevel(GetLocalPlayer(), InventoryPocketLevelDefinition, PocketLevelSpawnLocation);
		//bridgeSubsystem->StreamOutLevel(InventoryPocketLevelDefinition->IdentifingGameplayTag);
	}
	else
	{
		check(false && "Define a valid definition for the Inventory world");
	}
}
