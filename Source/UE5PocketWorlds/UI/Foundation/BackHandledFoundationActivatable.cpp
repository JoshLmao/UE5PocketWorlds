// Fill out your copyright notice in the Description page of Project Settings.


#include "BackHandledFoundationActivatable.h"
#include "Delegates/Delegate.h"
#include "Input/CommonUIInputTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BackHandledFoundationActivatable)

void UBackHandledFoundationActivatable::NativeOnInitialized()
{
	BackHandle = RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData, true, FSimpleDelegate::CreateUObject(this, &UBackHandledFoundationActivatable::HandleBackAction)));
}

void UBackHandledFoundationActivatable::HandleBackAction()
{
	DeactivateWidget();
}
