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

	// Toggle inventory screen open or closed
	void ToggleOpen(bool isOpen);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> InventoryRootWidget;

private:
	class UUserWidget* CreatedRoot;
};
