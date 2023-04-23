// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5PocketWorldsPlayerController.h"
#include "Component/PlayerInventoryComponent.h"
#include "CommonLocalPlayer.h"

AUE5PocketWorldsPlayerController::AUE5PocketWorldsPlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("Player Inventory Component"));
}

void AUE5PocketWorldsPlayerController::ToggleInventory(bool open)
{
	InventoryComponent->ToggleOpen(open);

	if (open) 
	{
		SetInputMode(FInputModeUIOnly());
	}
	else 
	{
		SetInputMode(FInputModeGameOnly());
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
