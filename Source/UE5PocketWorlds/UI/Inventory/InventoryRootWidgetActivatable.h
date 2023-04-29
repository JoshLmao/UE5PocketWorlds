// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Input/UIActionBindingHandle.h"
#include "CommonActivatableWidget.h"
#include "InventoryRootWidgetActivatable.generated.h"

/**
 * 
 */
UCLASS()
class UE5POCKETWORLDS_API UInventoryRootWidgetActivatable : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	void NativeOnInitialized() override;

	UFUNCTION()
	void HandleBackAction();

protected:
	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle BackInputActionData;
		
	FUIActionBindingHandle BackHandle;
};

