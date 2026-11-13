// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameCamera.h"
#include "GameCameraZoom.h"
#include "PlayerCharacter.h"
#include "Camera/CameraActor.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultMappingContext,0);
	}
	
	CameraActor= GetWorld()->SpawnActor<AGameCameraZoom>(GetPawn()->GetActorLocation(), GetPawn()-> GetActorRotation());
	SetViewTarget(CameraActor);
	CameraActor->ReceivePlayer(Cast<APlayerCharacter>(GetPawn()));
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
		EnhancedInput->BindAction(IAMove, ETriggerEvent::Canceled, this , &ACustomPlayerController::ActionInput);
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

void ACustomPlayerController::NewRoomEntered(FTransform newCameraTransform, UBoxComponent* newCameraLimits)
{
	if (CameraActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraActor NULLPTR"))
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Calling GameCamera"))
		CameraActor->UpdatePosition(newCameraTransform, newCameraLimits);
}
