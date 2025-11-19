// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveSceneObject.generated.h"

class UInteractiveObjectSelectionComponent;
class UInteractiveObjectMovementComponent;

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	Sphere,
	Cube
};

UCLASS()
class INTERACTIVEOBJECT_API AInteractiveSceneObject : public AActor
{
	GENERATED_BODY()

public:
	AInteractiveSceneObject();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interactive Object")
	UInteractiveObjectMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interactive Object")
	UInteractiveObjectSelectionComponent* SelectionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interactive Object")
	UStaticMeshComponent* StaticMeshComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interactive Object")
	EObjectType Type;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
