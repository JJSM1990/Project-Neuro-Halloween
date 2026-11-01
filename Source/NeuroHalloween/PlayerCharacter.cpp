// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "CustomPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RoomForwardVector = FVector::ZeroVector;
	RoomRightVector = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameController = Cast<ACustomPlayerController>(GetController());
	if (GameController != nullptr)
	{
		GameController->MovementDelegate.BindUObject(this, &APlayerCharacter::Move);
		GameController->ActionDelegate.BindUObject(this, &APlayerCharacter::Action);
	}

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::Move(FVector2D InputDirection) const
{
	FVector MovementDirection = RoomForwardVector * InputDirection.X + RoomRightVector * InputDirection.Y;
	if (MovementDirection.Length() > 1)
	{
		MovementDirection = MovementDirection.GetSafeNormal();
	}
	GetCharacterMovement() -> AddInputVector(MovementDirection);
	DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation()+ MovementDirection*200, 5, FColor::Red);
	DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation()+ GetActorForwardVector()*200, 5, FColor::Green);
}

void APlayerCharacter::Action(bool bAction)
{
	if (bAction)
	{
		//Por Hacer
	}
}

void APlayerCharacter::NewRoom(FTransform newTransform, UBoxComponent* newCameraLimits)
{
	if (GameController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GAMECONTROLLER NULLPTR"))
		return;
	}
	RoomForwardVector = newTransform.GetRotation().GetForwardVector();
	RoomRightVector = newTransform.GetRotation().GetRightVector();
	GameController -> NewRoomEntered(newTransform, newCameraLimits );
}