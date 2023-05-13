// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PlayerInventoryComponent.generated.h"

//Main component to control showing inventory to screen to player
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5POCKETWORLDS_API UPlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventoryComponent();

	// Opens in inventory to the screen of the player. Returns true if opened successfully
	bool Open();

	void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UFoundationBaseActivatable> InventoryRootWidget;

private:
	class UFoundationBaseActivatable* CreatedRoot;

	APlayerController* OwningPlayerController;

	// Handle listening to Inventory OnDeactivated
	FDelegateHandle InventoryDeactivatedHandle;

	UFUNCTION()
	void OnInventoryClosed();
};
