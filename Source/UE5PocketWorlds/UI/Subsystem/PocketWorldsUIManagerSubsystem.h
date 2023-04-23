// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"
#include "Containers/Ticker.h"
#include "GameUIManagerSubsystem.h"
#include "UObject/UObjectGlobals.h"

#include "PocketWorldsUIManagerSubsystem.generated.h"

/**
 * Copy of ULyraUIManagerSubsystem
 */
UCLASS()
class UE5POCKETWORLDS_API UPocketWorldsUIManagerSubsystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()
	
public:
	UPocketWorldsUIManagerSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	bool Tick(float DeltaTime);
	void SyncRootLayoutVisibilityToShowHUD();

	FTSTicker::FDelegateHandle TickHandle;
};
