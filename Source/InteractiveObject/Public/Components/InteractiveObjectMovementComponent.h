// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveObjectMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIVEOBJECT_API UInteractiveObjectMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractiveObjectMovementComponent();

	UFUNCTION(BlueprintCallable, Category="Movement")
	bool TryAndStartMovingObject(const APlayerController* InWho) noexcept;

	UFUNCTION(BlueprintCallable, Category="Movement")
	void StopMovingObject(const APlayerController* InWho) noexcept;

	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MovementInterpolationSpeed = 10.f;
	
	bool bMoving = false;

	UPROPERTY()
	const APlayerController* PlayerController;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
