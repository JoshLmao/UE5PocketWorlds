// Fill out your copyright notice in the Description page of Project Settings.


#include "PocketWorldsPrimaryGameLayout.h"


void UPocketWorldsPrimaryGameLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterLayer(FGameplayTag::RequestGameplayTag("UI.Layer.Game"), GameLayer);
	RegisterLayer(FGameplayTag::RequestGameplayTag("UI.Layer.GameMenu"), GameMenuLayer);
	RegisterLayer(FGameplayTag::RequestGameplayTag("UI.Layer.Menu"), MenuLayer);
	RegisterLayer(FGameplayTag::RequestGameplayTag("UI.Layer.Modal"), ModalLayer);
}
