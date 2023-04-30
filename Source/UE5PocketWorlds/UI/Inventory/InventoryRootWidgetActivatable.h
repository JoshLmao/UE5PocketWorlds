// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE5PocketWorlds/UI/Foundation/FoundationBaseActivatable.h"
#include "InventoryRootWidgetActivatable.generated.h"

/**
 * Root Activatable widget to contain inventory
 */
UCLASS(Abstract)
class UE5POCKETWORLDS_API UInventoryRootWidgetActivatable : public UFoundationBaseActivatable
{
	GENERATED_BODY()

	UInventoryRootWidgetActivatable();

public:
	UPROPERTY(meta = (BindWidget))
	class UCommonUserWidget* UW_InventoryContainer;
};

