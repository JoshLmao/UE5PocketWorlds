// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5PocketWorldsPlayerController.h"
#include "Component/PlayerInventoryComponent.h"

AUE5PocketWorldsPlayerController::AUE5PocketWorldsPlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("Player Inventory Component"));
}

void AUE5PocketWorldsPlayerController::ToggleInventory(bool open)
{
	InventoryComponent->ToggleOpen(open);
}
