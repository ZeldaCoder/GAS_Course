// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(imc);

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subsystem);

	subsystem->AddMappingContext(imc, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);

	
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>(InputComponent);

	input->BindAction(moveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::move);
	
}

void AAuraPlayerController::move(const FInputActionValue& value)
{
	const FVector2d moveInput = value.Get<FVector2d>();
	
	const FRotator rotation = GetControlRotation() ;
	const FRotator yawRotation = FRotator(0.0f, rotation.Yaw, 0.0f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forwardDirection, moveInput.Y);
		controlledPawn->AddMovementInput(rightDirection, moveInput.X);
	}
	
}
