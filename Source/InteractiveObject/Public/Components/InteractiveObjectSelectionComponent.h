// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveObjectSelectionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIVEOBJECT_API UInteractiveObjectSelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractiveObjectSelectionComponent();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelected, const bool, bSelected);

	UPROPERTY(BlueprintAssignable)
	FOnSelected OnSelected;

	UFUNCTION(BlueprintCallable, Category="Interactive Object")
	void SetSelected(const bool InSelected) noexcept;

	UFUNCTION(BlueprintPure, Category="Interactive Object")
	bool GetSelected() const noexcept
	{
		return bSelected;
	}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interactive Object")
	bool bSelected = false;
};
