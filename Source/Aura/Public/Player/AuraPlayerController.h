// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category= "Input")
		TObjectPtr<UInputMappingContext> imc;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> moveAction;

	void SetupInputComponent() override;

	void move(const FInputActionValue& value);
	
};
