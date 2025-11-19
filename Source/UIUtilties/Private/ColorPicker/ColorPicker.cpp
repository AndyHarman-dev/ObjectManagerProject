// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorPicker/ColorPicker.h"

#include "Runtime/AppFramework/Public/Widgets/Colors/SColorPicker.h"

UColorPicker::UColorPicker(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);

    InitialColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

    bShowInline = false;

    bUseAlpha = true;

    bForContextMenu = false;

    bShowOkCancelButtons = true;
}

TSharedRef<SWidget> UColorPicker::RebuildWidget()
{
    SlateColorPickerWidget = SNew(SColorPicker)
        .TargetColorAttribute(InitialColor)
        .DisplayInlineVersion(bShowInline)
        .UseAlpha(bUseAlpha)
        .OnColorPickerCancelled_Lambda([this](FLinearColor Color)
            {
                HandleColorCancelClicked(Color);
            })
        .OnColorCommitted_Lambda([this](const FLinearColor& NewColor)
            {
                HandleColorChanged(NewColor);
            });

    TSharedPtr<SButton> OkButton;
    TSharedPtr<SButton> CancelButton;

    OkButton = SNew(SButton)
        .Text(FText::FromString("OK"))
        .ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
        .OnClicked_Lambda([this]()
            {
                HandleColorOkClicked();
                return FReply::Handled();
            });

    CancelButton = SNew(SButton)
        .Text(FText::FromString("Cancel"))
        .OnClicked_Lambda([this]()
            {
                HandleColorCancelClicked(InitialColor);
                return FReply::Handled();
            });

    return SNew(SBorder)
        .BorderBackgroundColor(BackgroundColor)
        .BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
        .Padding(10)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SlateColorPickerWidget.ToSharedRef()
            ]
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SBox)
                    .Visibility(bShowOkCancelButtons ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed)
                    .Padding(2)
                    [
                        SNew(SHorizontalBox)
                            + SHorizontalBox::Slot()
                            .FillWidth(1.0f)
                            [
                                SNew(SBox)
                            ]
                            + SHorizontalBox::Slot()
                            .AutoWidth()
                            .HAlign(HAlign_Right)   
                            [
                                SNew(SBox)
                                    .Padding(2)
                                    .Visibility(!bForContextMenu ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed)
                                    [
                                        OkButton.ToSharedRef()
                                    ]         
                            ]
                            + SHorizontalBox::Slot()
                            .AutoWidth()
                            .HAlign(HAlign_Right)
                            .Padding(2)
                            [
                                CancelButton.ToSharedRef()
                            ]
                    ]
            ]
        ];   
}

void UColorPicker::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    SlateColorPickerWidget.Reset();
}

void UColorPicker::HandleColorOkClicked()
{
    OnContextMenuCloseRequested.Broadcast();
}

void UColorPicker::HandleColorCancelClicked(const FLinearColor& Color)
{
    OnColorChanged.Broadcast(Color);
    OnContextMenuCloseRequested.Broadcast();
}

void UColorPicker::HandleColorChanged(const FLinearColor& NewColor)
{
    OnColorChanged.Broadcast(NewColor);
}