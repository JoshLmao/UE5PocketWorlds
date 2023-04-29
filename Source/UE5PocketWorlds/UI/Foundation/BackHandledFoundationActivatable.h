// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE5PocketWorlds/UI/Foundation/FoundationBaseActivatable.h"
#include "Engine/DataTable.h"
#include "Input/UIActionBindingHandle.h"
#include "BackHandledFoundationActivatable.generated.h"

/**
 * A foundation activatable base, with additional feature of being able to handle a "Back" input
 */
UCLASS()
class UE5POCKETWORLDS_API UBackHandledFoundationActivatable : public UFoundationBaseActivatable
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
