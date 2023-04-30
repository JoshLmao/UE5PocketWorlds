#include "PocketLevelStageManager.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "PocketCaptureSubsystem.h"
#include "PocketCapture.h"

APocketLevelStageManager::APocketLevelStageManager()
{
	PrimaryActorTick.bCanEverTick = false;

	ActorSpawnPointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Actor Spawn Point Component"));
}

void APocketLevelStageManager::BeginPlay()
{
	Super::BeginPlay();
	
	// 1
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, spawnParams);

	FAttachmentTransformRules attachRules(EAttachmentRule::KeepWorld, true);
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
