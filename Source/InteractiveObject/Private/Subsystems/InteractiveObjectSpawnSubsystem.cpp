// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/InteractiveObjectSpawnSubsystem.h"
#include "InteractiveSceneObject.h"

DEFINE_LOG_CATEGORY_STATIC(LogInteractiveSceneObjectSpawnSubsystem, Log, All);

AInteractiveSceneObject* UInteractiveObjectSpawnSubsystem::SpawnInteractiveObject(TSubclassOf<AInteractiveSceneObject> InClass, const FVector& InLocation, const FVector& InScale) noexcept
{
	const auto NewObject = GetWorld()->SpawnActor<AInteractiveSceneObject>(InClass, InLocation, FRotator::ZeroRotator);
	NewObject->SetActorScale3D(InScale);
	OnNewObjectSpawned.Broadcast(NewObject);
	return NewObject;
}

void UInteractiveObjectSpawnSubsystem::DestroyInteractiveObject(AInteractiveSceneObject* InObject) noexcept
{
	if (!IsValid(InObject))
	{
		UE_LOG(LogInteractiveSceneObjectSpawnSubsystem, Warning, TEXT("%hs: Tried to destroy null object"), __FUNCTION__);
		return;
	}

	InObject->Destroy();
	OnObjectRemoved.Broadcast(InObject);
}
