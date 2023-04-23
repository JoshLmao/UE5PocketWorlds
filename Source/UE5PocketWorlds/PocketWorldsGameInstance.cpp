// Fill out your copyright notice in the Description page of Project Settings.


#include "PocketWorldsGameInstance.h"

int32 UPocketWorldsGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	auto pc = NewPlayer->GetPlayerController(GetWorld());
	
	
	auto id = Super::AddLocalPlayer(NewPlayer, UserId);

	return id;
}

bool UPocketWorldsGameInstance::RemoveLocalPlayer(ULocalPlayer* ExistingPlayer)
{
	return Super::RemoveLocalPlayer(ExistingPlayer);
}
