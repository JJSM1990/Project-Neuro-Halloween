// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "CustomPlayerController.h"
#include "IInteractableObject.h"
#include "Animation/AnimInstanceProxy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	SphereComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	RoomForwardVector = FVector::ZeroVector;
	RoomRightVector = FVector::ZeroVector;
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
}

void APlayerCharacter::Action(bool bAction)
{
	UE_LOG(LogTemp, Display, TEXT("Action"));
	if (bAction)
	{
		TArray<AActor*> OverlappingActors;
		SphereComponent->GetOverlappingActors(OverlappingActors);
		if (OverlappingActors.Num() > 0)
		{
			for (AActor* OverlappingActor : OverlappingActors)
			{
				UE_LOG(LogTemp, Display, TEXT("Overlapping Actors"));
				if (OverlappingActor->Implements<UIInteractableObject>())
				{
					UE_LOG(LogTemp, Display, TEXT("Calling Object Interaction"));
					Cast<IIInteractableObject>(OverlappingActor) -> ObjectInteraction();
				}
			}
		} else
		{
			UE_LOG(LogTemp, Display, TEXT("Actors Not Found"));
		}

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