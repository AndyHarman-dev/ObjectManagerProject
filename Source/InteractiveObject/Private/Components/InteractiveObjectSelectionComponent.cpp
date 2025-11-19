// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractiveObjectSelectionComponent.h"


UInteractiveObjectSelectionComponent::UInteractiveObjectSelectionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractiveObjectSelectionComponent::SetSelected(const bool InSelected) noexcept
{
	if (bSelected != InSelected)
	{
		bSelected = InSelected;
		OnSelected.Broadcast(bSelected);
	}
}


