#include "RevolvingActorComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
URevolvingActorComponent::URevolvingActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void URevolvingActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get current rotation, add on per frame rotation and set as new rotation
	auto currentRotation = GetOwner()->GetActorRotation();
	currentRotation += RotationPerFrame;
	GetOwner()->SetActorRotation(currentRotation);
}

