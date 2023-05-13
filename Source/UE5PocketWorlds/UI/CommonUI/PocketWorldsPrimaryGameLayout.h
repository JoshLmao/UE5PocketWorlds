// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryGameLayout.h"
#include "PocketWorldsPrimaryGameLayout.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UE5POCKETWORLDS_API UPocketWorldsPrimaryGameLayout : public UPrimaryGameLayout
{
	GENERATED_BODY()
	
public:
	// Game HUD
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCommonActivatableWidgetStack* GameLayer;

	// Menus that are game-related, inventory UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCommonActivatableWidgetStack* GameMenuLayer;

	// Menus, full screen widgets such as Pause Menu/Options/Settings, etc
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UCommonActivatableWidgetStack* MenuLayer;

	// Confirmation/error dialogs, other modal-like widgets
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCommonActivatableWidgetStack* ModalLayer;

public:
	void NativeOnInitialized() override;
};
