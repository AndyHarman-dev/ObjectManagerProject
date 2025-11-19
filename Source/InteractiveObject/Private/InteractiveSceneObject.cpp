// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveSceneObject.h"

#include "Components/InteractiveObjectMovementComponent.h"
#include "Components/InteractiveObjectSelectionComponent.h"


AInteractiveSceneObject::AInteractiveSceneObject()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MovementComponent = CreateDefaultSubobject<UInteractiveObjectMovementComponent>(TEXT("MovementComponent"));
	SelectionComponent = CreateDefaultSubobject<UInteractiveObjectSelectionComponent>(TEXT("SelectionComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AInteractiveSceneObject::BeginPlay()
{
	Super::BeginPlay();
	
}

