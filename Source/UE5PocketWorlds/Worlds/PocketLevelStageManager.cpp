#include "PocketLevelStageManager.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "PocketCaptureSubsystem.h"
#include "PocketCapture.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

APocketLevelStageManager::APocketLevelStageManager()
{
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetMobility(EComponentMobility::Type::Static);	//make static to allow for children/child actors
	
	// Set as root component of the manager
	RootComponent = RootSceneComponent;

	ActorSpawnPointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ActorSpawnPointComponent"));
	ActorSpawnPointComponent->SetupAttachment(RootSceneComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootSceneComponent);
	CameraComponent->SetRelativeLocation(FVector(400.0f, 0.0f, 100.0f));
	CameraComponent->SetRelativeRotation(FRotator(-10.0f, -180.0f, 0.0f));
	// FoV/Aspect ratio
	CameraComponent->bConstrainAspectRatio = false;
	CameraComponent->SetAspectRatio(0.5f);
	CameraComponent->SetFieldOfView(20.0f);
}

void APocketLevelStageManager::BeginPlay()
{
	Super::BeginPlay();
	
	// 1
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, spawnParams);

	FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, true);
	SpawnedActor->AttachToComponent(ActorSpawnPointComponent, attachRules);

	// 2
	auto* pocketCaptureSubsys = GetWorld()->GetSubsystem<UPocketCaptureSubsystem>();
	PocketCaptureInst = pocketCaptureSubsys->CreateThumbnailRenderer(PocketCaptureClass);
	PocketCaptureInst->SetRenderTargetSize(1024, 2048);
	PocketCaptureInst->SetCaptureTarget(this);
}

UPocketCapture* APocketLevelStageManager::GetPocketCapture()
{
	return PocketCaptureInst;
}
