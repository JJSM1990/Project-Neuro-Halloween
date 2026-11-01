// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultMappingContext,0);
	}
}

void ACustomPlayerController::SetupInputComponent() 
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(IAMove, ETriggerEvent::Started, this , &ACustomPlayerController::MoveInput);
		EnhancedInput->BindAction(IAMove, ETriggerEvent::Triggered, this , &ACustomPlayerController::MoveInput);
		EnhancedInput->BindAction(IAMove, ETriggerEvent::Canceled, this , &ACustomPlayerController::MoveInput);

		EnhancedInput->BindAction(IAAction, ETriggerEvent::Started, this , &ACustomPlayerController::ActionInput);
	}
	
}
void ACustomPlayerController::MoveInput(const FInputActionValue &value) 
{
	FVector2D InputDirection = value.Get<FVector2D>();
	MovementDelegate.Execute(InputDirection);
}

void ACustomPlayerController::ActionInput(const FInputActionValue &value)
{
	bool bAction = value.Get<bool>();
	ActionDelegate.Execute(bAction);
}
