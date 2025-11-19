// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "InteractiveObjectSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig)
class INTERACTIVEOBJECT_API UInteractiveObjectSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	
	UPROPERTY(Config, EditAnywhere, Category="Interactive Object")
	TEnumAsByte<ECollisionChannel> InteractiveObjectDefaultCollision;
};
