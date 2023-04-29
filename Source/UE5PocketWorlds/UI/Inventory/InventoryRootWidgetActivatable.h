// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Input/UIActionBindingHandle.h"
#include "CommonActivatableWidget.h"
#include "InventoryRootWidgetActivatable.generated.h"

UENUM(BlueprintType)
enum class ELyraWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

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

public:
	//~UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End of UCommonActivatableWidget interface

protected:
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	ELyraWidgetInputMode InputConfig = ELyraWidgetInputMode::Default;

	/** The desired mouse behavior when the game gets input. */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;

};

