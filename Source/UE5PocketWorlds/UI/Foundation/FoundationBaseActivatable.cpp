// Fill out your copyright notice in the Description page of Project Settings.


#include "FoundationBaseActivatable.h"
#include "UE5PocketWorlds/UE5PocketWorlds.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FoundationBaseActivatable)

UFoundationBaseActivatable::UFoundationBaseActivatable()
{
	bIsBackHandler = true;
}

TOptional<FUIInputConfig> UFoundationBaseActivatable::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
		case ELyraWidgetInputMode::GameAndMenu:
			return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
		case ELyraWidgetInputMode::Game:
			return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
		case ELyraWidgetInputMode::Menu:
			return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		case ELyraWidgetInputMode::Default:
		default:
			return TOptional<FUIInputConfig>();
	}
}

bool UFoundationBaseActivatable::NativeOnHandleBackAction()
{
	UE_LOG(LogUIDebug, Log, TEXT("%s: Activatable closed via back handle"), *GetName());
	return Super::NativeOnHandleBackAction();
}
