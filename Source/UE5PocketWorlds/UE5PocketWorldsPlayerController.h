// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Component/PlayerInventoryComponent.h"

#include "UE5PocketWorldsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5POCKETWORLDS_API AUE5PocketWorldsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AUE5PocketWorldsPlayerController();

	void ToggleInventory(bool open);

	void ReceivedPlayer() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPlayerInventoryComponent* InventoryComponent;
};
