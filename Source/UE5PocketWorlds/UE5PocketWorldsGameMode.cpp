// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5PocketWorldsGameMode.h"
#include "UE5PocketWorldsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5PocketWorldsPlayerController.h"

AUE5PocketWorldsGameMode::AUE5PocketWorldsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerControllerClass = AUE5PocketWorldsPlayerController::StaticClass();
}
