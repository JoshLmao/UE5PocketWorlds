// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryRootWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5POCKETWORLDS_API UInventoryRootWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	void CloseRootWidget();
};

