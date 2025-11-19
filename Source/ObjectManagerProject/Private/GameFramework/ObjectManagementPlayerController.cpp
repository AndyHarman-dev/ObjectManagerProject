// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ObjectManagementPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Components/InteractiveObjectMovementComponent.h"
#include "Components/InteractiveObjectSelectionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Settings/InteractiveObjectSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogObjectManagementPlayerController, Log, All);

AObjectManagementPlayerController::AObjectManagementPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AObjectManagementPlayerController::LookAt(FVector Location) noexcept
{
	TargetLookLocation = Location;
	bIsRotatingToTarget = true;
}

void AObjectManagementPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TickLookingAtTargetLocation(DeltaSeconds);
}

AActor* AObjectManagementPlayerController::TraceForActorUnderCursor() noexcept
{
	const auto ObjectSettings = GetDefault<UInteractiveObjectSettings>();

	FHitResult HitResult;
	GetHitResultUnderCursor(ObjectSettings->InteractiveObjectDefaultCollision, false, HitResult);
	return HitResult.GetActor();
}

FHitResult AObjectManagementPlayerController::GetHitResultAtViewPoint() noexcept
{
	if (!IsValid(ControlledPawn))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: Pawn is invalid!"), __FUNCTION__);
		return {};
	}

	FVector Location = ControlledPawn->GetActorLocation();
	Location.Z += ControlledPawn->BaseEyeHeight;

	const auto ForwardVector = UKismetMathLibrary::GetForwardVector(PlayerCameraManager->GetCameraRotation());
	const auto Destination = Location + ForwardVector * 1000;
	
	FHitResult OutHitResult;
	GetWorld()->LineTraceSingleByChannel(OutHitResult, Location, Destination, ECC_Visibility);
	return OutHitResult;
}

void AObjectManagementPlayerController::Reselect(AActor* InActor)
{
	DeselectCurrentActor();
	Select(InActor);
}

void AObjectManagementPlayerController::DeselectCurrentActor()
{
	if (!IsValid(CurrentlySelectedActor))
	{
		return;
	}

	const auto SelectionComponent = CurrentlySelectedActor->FindComponentByClass<UInteractiveObjectSelectionComponent>();
	if (!ensureMsgf(IsValid(SelectionComponent), TEXT("%hs: SelectionComponent is null for selectable actor!"), __FUNCTION__))
	{
		return;
	}

	SelectionComponent->SetSelected(false);
	OnObjectDeselected.Broadcast(CurrentlySelectedActor);
	CurrentlySelectedActor = nullptr;
}

void AObjectManagementPlayerController::TickLookingAtTargetLocation(float DeltaSeconds)
{
	if (bIsRotatingToTarget && GetPawn())
	{
		FVector PawnLocation = GetPawn()->GetActorLocation();
        
		FVector Direction = TargetLookLocation - PawnLocation;
		Direction.Z = 0;
        
		if (Direction.SizeSquared() > 0.01f)
		{
			FRotator TargetRotation = Direction.Rotation();
            
			FRotator CurrentRotation = GetControlRotation();
            
			FRotator NewRotation = FMath::RInterpTo(
				CurrentRotation,
				TargetRotation,
				DeltaSeconds,
				LookRotationSpeed
			);
            
			SetControlRotation(NewRotation);
            
			float AngleDiff = FMath::Abs(FMath::FindDeltaAngleDegrees(
				CurrentRotation.Yaw,
				TargetRotation.Yaw
			));
            
			if (AngleDiff < RotationTolerance)
			{
				bIsRotatingToTarget = false;
			}
		}
	}
}

UEnhancedInputLocalPlayerSubsystem* AObjectManagementPlayerController::GetLocalPlayerSubsystem() const
{
	const auto LocalPlayer = GetLocalPlayer();
	if (!IsValid(LocalPlayer))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: LocalPlayer was null!"), __FUNCTION__);
		return nullptr;
	}
	
	const auto EnhancedInputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(EnhancedInputSubsystem))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: Enhanced input world subsystem isn't activated!"), __FUNCTION__);
		return nullptr;
	}

	return EnhancedInputSubsystem;
}

void AObjectManagementPlayerController::SetupInputMapping() const
{
	if (!IsValid(InputSettings.InputMappingContext))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: InputMappingContext was null!"), __FUNCTION__);
		return;
	}
	
	const auto EnhancedInputSubsystem = GetLocalPlayerSubsystem();
	if (!IsValid(EnhancedInputSubsystem))
	{
		return;
	}
	
	EnhancedInputSubsystem->AddMappingContext(InputSettings.InputMappingContext, InputSettings.InputPriority, InputSettings.ContextOptions);
}

void AObjectManagementPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetupInputMapping();
	SetShowMouseCursor(true);
}

void AObjectManagementPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledPawn = InPawn;
}

void AObjectManagementPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	ControlledPawn = nullptr;
}

void AObjectManagementPlayerController::HandleLookInput(const FInputActionValue& InputActionValue)
{
	if (bIsRotatingToTarget)
	{
		return;
	}
	
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(-LookAxisVector.Y);
}

void AObjectManagementPlayerController::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveAxisVector = InputActionValue.Get<FVector2D>();
	if (!IsValid(ControlledPawn))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: ControlledPawn is null!"), __FUNCTION__);
		return;
	}

	const FRotator ControllerRotation = GetControlRotation();
	const FRotator YawRotation(0, ControllerRotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledPawn->AddMovementInput(ForwardDirection, MoveAxisVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MoveAxisVector.X);
}

void AObjectManagementPlayerController::HandleClickedInput()
{
	const auto HitActor = TraceForActorUnderCursor();
	if (!IsValid(HitActor))
	{
		DeselectCurrentActor();
		return;
	}

	Reselect(HitActor);
}

void AObjectManagementPlayerController::HandleClickAndHold()
{
	if (IsValid(MovementComponent))
	{
		return;
	}

	if (!IsValid(CurrentlySelectedActor))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: Currently selected actor must be valid!"), __FUNCTION__);
		return;
	}

	const auto MovComponent = CurrentlySelectedActor->FindComponentByClass<UInteractiveObjectMovementComponent>();
	if (!IsValid(MovComponent))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: Currently selected actor must have movement component!"), __FUNCTION__);
		return;
	}

	MovComponent->TryAndStartMovingObject(this);
	MovementComponent = MovComponent;
}

void AObjectManagementPlayerController::HandleClickAndHoldCompleted()
{
	if (!IsValid(CurrentlySelectedActor))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: Currently selected actor must be valid!"), __FUNCTION__);
		return;
	}
	
	MovementComponent->StopMovingObject(this);
	MovementComponent = nullptr;
}

void AObjectManagementPlayerController::SetupEnhancedInputBindings()
{
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		UE_LOG(LogObjectManagementPlayerController, Error, TEXT("%hs: Enhanced Input Component isn't enabled in project settings!"), __FUNCTION__);
		return;
	}

	EnhancedInputComponent->BindAction(InputActions.Look, ETriggerEvent::Triggered, this, &ThisClass::HandleLookInput);
	EnhancedInputComponent->BindAction(InputActions.Move, ETriggerEvent::Triggered, this, &ThisClass::HandleMoveInput);
		
	EnhancedInputComponent->BindAction(InputActions.ClickAndHold, ETriggerEvent::Started, this, &ThisClass::HandleClickedInput);
	EnhancedInputComponent->BindAction(InputActions.ClickAndHold, ETriggerEvent::Triggered, this, &ThisClass::HandleClickAndHold);
	EnhancedInputComponent->BindAction(InputActions.ClickAndHold, ETriggerEvent::Completed, this, &ThisClass::HandleClickAndHoldCompleted);
}

void AObjectManagementPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	SetupEnhancedInputBindings();
}

void AObjectManagementPlayerController::Select(AActor* InActor)
{
	if (!IsValid(InActor) || !IsValid(InActor->FindComponentByClass<UInteractiveObjectSelectionComponent>()) || InActor == CurrentlySelectedActor)
	{
		return;
	}

	const auto SelectionComponent = InActor->FindComponentByClass<UInteractiveObjectSelectionComponent>();
	SelectionComponent->SetSelected(true);
	
	CurrentlySelectedActor = InActor;
	OnObjectSelected.Broadcast(InActor);
	
	LookAt(CurrentlySelectedActor->GetActorLocation());
}

