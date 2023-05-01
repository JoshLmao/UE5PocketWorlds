

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RevolvingActorComponent.generated.h"


// Component to slowly rotate an actor in the set direction
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5POCKETWORLDS_API URevolvingActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URevolvingActorComponent();

	UPROPERTY(EditDefaultsOnly)
	FRotator RotationPerFrame;

public:	
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
