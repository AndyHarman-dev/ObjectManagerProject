// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractiveObjectMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSceneObjectMovementComponent, Log, All);

UInteractiveObjectMovementComponent::UInteractiveObjectMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UInteractiveObjectMovementComponent::TryAndStartMovingObject(APlayerController* InWho) noexcept
{
	if (!IsValid(InWho))
	{
		UE_LOG(LogSceneObjectMovementComponent, Error, TEXT("%hs: InWho was null when tried to move object!"), __FUNCTION__);
		return false;
	}

	if (bMoving)
	{
		UE_LOG(LogSceneObjectMovementComponent, Warning, TEXT("%hs: Object is already moving!"), __FUNCTION__);
		return false;
	}

	PlayerController = InWho;
	bMoving = true;
	SetComponentTickEnabled(true);
	return true;
}

void UInteractiveObjectMovementComponent::StopMovingObject(APlayerController* InWho) noexcept
{
	if (InWho != PlayerController)
	{
		UE_LOG(LogSceneObjectMovementComponent, Error, TEXT("%hs: %s doesn't own this movement!"), __FUNCTION__, *GetNameSafe(InWho));
		return;
	}

	bMoving = false;
	PlayerController = nullptr;
	SetComponentTickEnabled(false);
}

void UInteractiveObjectMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
}

void UInteractiveObjectMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bMoving)
	{
		FHitResult HitResult;
		if (!PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			return;
		}

		if (HitResult.GetActor() == GetOwner())
		{
			return;
		}

		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = HitResult.Location;
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MovementInterpolationSpeed);
       
		GetOwner()->SetActorLocation(NewLocation);
	}
}

