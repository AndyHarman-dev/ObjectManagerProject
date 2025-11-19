// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractiveObjectSpawnSubsystem.generated.h"

class AInteractiveSceneObject;
/**
 * 
 */
UCLASS(BlueprintType)
class INTERACTIVEOBJECT_API UInteractiveObjectSpawnSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewObjectSpawned, const AActor*, InObject);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectRemoved, const AActor*, InObject);

	UPROPERTY(BlueprintAssignable)
	FOnNewObjectSpawned OnNewObjectSpawned;

	UPROPERTY(BlueprintAssignable)
	FOnObjectRemoved OnObjectRemoved;
	
	UFUNCTION(BlueprintCallable, Category="Interactive Object")
	AInteractiveSceneObject* SpawnInteractiveObject(TSubclassOf<AInteractiveSceneObject> InClass, const FVector& InLocation, const FVector& InScale) noexcept;

	UFUNCTION(BlueprintCallable, Category="Interactive Object")
	void DestroyInteractiveObject(AInteractiveSceneObject* InObject) noexcept;
};
