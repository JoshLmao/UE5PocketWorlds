#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Component/PlayerInventoryComponent.h"

#include "UE5PocketWorldsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5POCKETWORLDS_API AUE5PocketWorldsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AUE5PocketWorldsPlayerController();

	void BeginPlay() override;

	void ToggleInventory(bool open);

	void ReceivedPlayer() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPlayerInventoryComponent* InventoryComponent;

	TSubclassOf<class UFoundationBaseActivatable> PlayerHUDWidgetClass;
};
