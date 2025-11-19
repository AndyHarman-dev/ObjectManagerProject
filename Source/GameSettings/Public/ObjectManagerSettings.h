// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveSceneObject.h"
#include "UObject/Object.h"
#include "ObjectManagerSettings.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAMESETTINGS_API UObjectManagerSettings : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static UObjectManagerSettings* GetObjectManagerSettings()
	{
		return GetMutableDefault<UObjectManagerSettings>();
	}

	UFUNCTION(BlueprintCallable)
	void SaveDefaultObjectType(const EObjectType InType) noexcept;

	UFUNCTION(BlueprintCallable)
	void SaveDefaultObjectColor(const FLinearColor InColor) noexcept;

	UFUNCTION(BlueprintCallable)
	void SaveDefaultObjectScale(const FVector InScale) noexcept;

	UFUNCTION(BlueprintCallable)
	EObjectType LoadDefaultObjectType() noexcept;

	UFUNCTION(BlueprintCallable)
	FLinearColor LoadDefaultObjectColor() noexcept;

	UFUNCTION(BlueprintCallable)
	FVector LoadDefaultObjectScale() noexcept;

private:
	FCriticalSection CriticalSection;
};
