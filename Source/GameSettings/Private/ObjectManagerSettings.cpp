// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManagerSettings.h"

void UObjectManagerSettings::SaveDefaultObjectType(const EObjectType InType) noexcept
{
	FScopeLock Guard(&CriticalSection); 
	GConfig->SetInt(TEXT("UserSettings"), TEXT("DefaultObjectType"), static_cast<int32>(InType), GGameUserSettingsIni);
	GConfig->Flush(false, GGameUserSettingsIni);
}

void UObjectManagerSettings::SaveDefaultObjectColor(const FLinearColor InColor) noexcept
{
	FScopeLock Guard(&CriticalSection); 
	GConfig->SetColor(TEXT("UserSettings"), TEXT("DefaultObjectColor"), InColor.ToFColor(true), GGameUserSettingsIni);
	GConfig->Flush(false, GGameUserSettingsIni);
}

void UObjectManagerSettings::SaveDefaultObjectScale(const FVector InScale) noexcept
{
	FScopeLock Guard(&CriticalSection); 
	GConfig->SetVector(TEXT("UserSettings"), TEXT("DefaultObjectScale"), InScale, GGameUserSettingsIni);
	GConfig->Flush(false, GGameUserSettingsIni);
}

EObjectType UObjectManagerSettings::LoadDefaultObjectType() noexcept
{
	FScopeLock Guard(&CriticalSection); 
	int32 TypeValue = 0;
	GConfig->GetInt(TEXT("UserSettings"), TEXT("DefaultObjectType"), TypeValue, GGameUserSettingsIni);
	return static_cast<EObjectType>(TypeValue);
}

FLinearColor UObjectManagerSettings::LoadDefaultObjectColor() noexcept
{
	FScopeLock Guard(&CriticalSection); 
	FColor ColorValue;
	GConfig->GetColor(TEXT("UserSettings"), TEXT("DefaultObjectColor"), ColorValue, GGameUserSettingsIni);
	return FLinearColor(ColorValue);
}

FVector UObjectManagerSettings::LoadDefaultObjectScale() noexcept
{
	FScopeLock Guard(&CriticalSection); 
	FVector ScaleValue = FVector::OneVector;
	GConfig->GetVector(TEXT("UserSettings"), TEXT("DefaultObjectScale"), ScaleValue, GGameUserSettingsIni);
	return ScaleValue;
}