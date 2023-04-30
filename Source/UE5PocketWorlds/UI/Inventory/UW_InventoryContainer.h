#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UW_InventoryContainer.generated.h"

/**
 * Root container to encompass whole inventory
 */
UCLASS()
class UE5POCKETWORLDS_API UUW_InventoryContainer : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	// 3D player view
	UPROPERTY(meta = (BindWidget))
	class UCommonUserWidget* PlayerRepresentation;

	/* @todo
	// Container widget to encase main inventory
	UPROPERTY(meta = (BindWidget))
	class UCommonUserWidget* InventorySlotsContainer;
	*/
};
