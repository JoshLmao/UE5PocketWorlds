// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryRootWidgetActivatable.h"
#include "Containers/Array.h"
#include "Delegates/Delegate.h"
#include "Input/CommonUIInputTypes.h"
#include "Templates/Casts.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(InventoryRootWidgetActivatable)

void UInventoryRootWidgetActivatable::NativeOnInitialized()
{
	BackHandle = RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData, true, FSimpleDelegate::CreateUObject(this, &UInventoryRootWidgetActivatable::HandleBackAction)));
}

void UInventoryRootWidgetActivatable::HandleBackAction()
{
	DeactivateWidget();
}
