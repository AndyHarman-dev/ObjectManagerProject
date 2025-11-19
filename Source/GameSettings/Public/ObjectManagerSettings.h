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
	static const UObjectManagerSettings* GetObjectManagerSettings()
	{
		return GetDefault<UObjectManagerSettings>();
	}

	UFUNCTION(BlueprintCallable)
	void SaveDefaultObjectType(const EObjectType InType) const noexcept;

	UFUNCTION(BlueprintCallable)
	void SaveDefaultObjectColor(const FLinearColor InColor) const noexcept;

	UFUNCTION(BlueprintCallable)
	void SaveDefaultObjectScale(const FVector InScale) const noexcept;

	UFUNCTION(BlueprintCallable)
	EObjectType LoadDefaultObjectType() const noexcept;

	UFUNCTION(BlueprintCallable)
	FLinearColor LoadDefaultObjectColor() const noexcept;

	UFUNCTION(BlueprintCallable)
	FVector LoadDefaultObjectScale() const noexcept;

private:
	mutable FCriticalSection CriticalSection;
};
