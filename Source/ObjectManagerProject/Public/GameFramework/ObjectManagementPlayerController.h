// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InteractiveSceneObject.h"
#include "GameFramework/PlayerController.h"
#include "ObjectManagementPlayerController.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;

USTRUCT(Blueprintable)
struct FInputMappingContextSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Management")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Management")
	int32 InputPriority;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Management")
	FModifyContextOptions ContextOptions;
};

USTRUCT(Blueprintable)
struct FInputActions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Input")
	UInputAction* Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Input")
	UInputAction* Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Input")
	UInputAction* ClickAndHold;
};

/**
 * 
 */
UCLASS()
class OBJECTMANAGERPROJECT_API AObjectManagementPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AObjectManagementPlayerController();
	
	UFUNCTION(BlueprintCallable, Category="Object Management")
	void LookAt(FVector Location) noexcept;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category="Object Management")
	AActor* TraceForActorUnderCursor() noexcept;

	UFUNCTION(BlueprintPure)
	FHitResult GetHitResultAtViewPoint() noexcept;

	UFUNCTION(BlueprintCallable, Category="Object Management")
	void Reselect(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="Object Management")
	void DeselectCurrentActor();
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Object Management")
	float LookRotationSpeed = 3.0f;
	bool bIsRotatingToTarget;
	FVector TargetLookLocation;
	float RotationTolerance = 1.0f; // Degrees of tolerance before we stop rotating
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Management")
	FInputMappingContextSettings InputSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Object Management")
	FInputActions InputActions;
	
	UEnhancedInputLocalPlayerSubsystem* GetLocalPlayerSubsystem() const;
	void SetupInputMapping() const;
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	

	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	void HandleClickedInput();
	void HandleClickAndHold();
	void HandleClickAndHoldCompleted();
	void SetupEnhancedInputBindings();
	virtual void SetupInputComponent() override;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectSelected, AActor*, InObject);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDeselected, AActor*, InObject);

	UPROPERTY(BlueprintAssignable)
	FOnObjectSelected OnObjectSelected;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectDeselected OnObjectDeselected;
	
private:
	UPROPERTY()
	APawn* ControlledPawn;

	UPROPERTY()
	AActor* CurrentlySelectedActor;
	UPROPERTY()
	UInteractiveObjectMovementComponent* MovementComponent;

	void Select(AActor* InActor);

};
