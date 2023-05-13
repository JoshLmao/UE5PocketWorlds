

#pragma once

#include "CoreMinimal.h"
#include "PocketLevel.h"
#include "GameplayTagContainer.h"
#include "IdentifyingPocketLevel.generated.h"

/**
 * 
 */
UCLASS()
class UE5POCKETWORLDS_API UIdentifyingPocketLevel : public UPocketLevel
{
	GENERATED_BODY()
	
public:
	// Gameplay Tag to identify the created pocket world
	UPROPERTY(EditAnywhere)
	FGameplayTag IdentifingGameplayTag;
};
