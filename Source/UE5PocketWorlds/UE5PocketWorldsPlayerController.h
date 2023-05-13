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
	// Component to interface with Inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPlayerInventoryComponent* InventoryComponent;

	// Widget class to spawn and use for Player HUD
	UPROPERTY()
	TSubclassOf<class UFoundationBaseActivatable> PlayerHUDWidgetClass;

	// Data asset that defines the inventory pocket level to use
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Pocket World Config")
	class UIdentifyingPocketLevel* InventoryPocketLevelDefinition;

	// Location in current level to spawn the pocket level
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Pocket World Config")
	FVector PocketLevelSpawnLocation = FVector::ZeroVector;

private:
	void InitInventoryPocketWorld();
};
