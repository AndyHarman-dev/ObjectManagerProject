// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "ColorPicker.generated.h"

class SColorPicker;
/**
 * 
 */
UCLASS(BlueprintType)
class UIUTILTIES_API UColorPicker : public UWidget
{
	GENERATED_BODY()
public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UColorPicker(const FObjectInitializer& ObjectInitializer);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnColorChanged, const FLinearColor&, NewColor);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnContextMenuCloseRequested);

	UPROPERTY(BlueprintAssignable, Category = "Blueprint Color Picker")
	FOnColorChanged OnColorChanged;

	UPROPERTY(BlueprintAssignable, Category = "Blueprint Color Picker")
	FOnContextMenuCloseRequested OnContextMenuCloseRequested;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	FLinearColor InitialColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	FLinearColor BackgroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	bool bShowInline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	bool bUseAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	bool bForContextMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	bool bShowOkCancelButtons;

private:
	TSharedPtr<SColorPicker> SlateColorPickerWidget;

	void HandleColorChanged(const FLinearColor& NewColor);
	void HandleColorOkClicked();
	void HandleColorCancelClicked(const FLinearColor& PreviousColor);
};
