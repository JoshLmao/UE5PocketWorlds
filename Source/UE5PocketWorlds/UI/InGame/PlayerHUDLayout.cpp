// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDLayout.h"

UPlayerHUDLayout::UPlayerHUDLayout()
{
	bIsBackHandler = false;
	InputConfig = ELyraWidgetInputMode::Game;
	GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;
}