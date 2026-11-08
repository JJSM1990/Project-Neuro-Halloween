// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCamera.h"

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootEmpty = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootEmpty);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(RootEmpty);
	RoomActive = false;
	deltaZ = 100.f;
	deltaX = -700.f;
	deltaY = 0.f;
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerCharacter != nullptr)
	{
		PlayerLocation = PlayerCharacter->GetActorLocation();
	} else
	{
		PlayerLocation = FVector::ZeroVector;
	}
	UpdateCameraCompLocationTick(DeltaTime);
	UpdateCameraRotation();
}

void AGameCamera::ReceivePlayer(APlayerCharacter* playerCharacter)
{
	PlayerCharacter = playerCharacter;
}

void AGameCamera::UpdatePosition(FTransform newTranform, UBoxComponent* CameraLimits)
{
	UE_LOG(LogTemp, Display, TEXT("Game Camera Called"));
	RoomActive = true;
	FVector CameraCurrentLocation = CameraComp -> GetComponentLocation();
	SetActorRotation(newTranform.GetRotation());
	SetActorLocation(newTranform.GetLocation());
	CameraComp -> SetWorldLocation(CameraCurrentLocation);
	XLimit = CameraLimits->GetUnscaledBoxExtent().X;
	YLimit = CameraLimits->GetUnscaledBoxExtent().Y;
	ZLimit = CameraLimits->GetUnscaledBoxExtent().Z;
	
}

void AGameCamera::UpdateCameraCompLocationTick(float deltaTime)
{
	FVector CurrentLocation = CameraComp->GetRelativeLocation();
	CameraComp->SetWorldLocation(PlayerLocation);
	FVector CameraCompRelativeLocation = CameraComp->GetRelativeLocation() + FVector(deltaX, deltaY, deltaZ);
	
	if (CameraCompRelativeLocation.X > XLimit)
	{
		CameraCompRelativeLocation.X= XLimit;
	} else if (CameraCompRelativeLocation.X < -XLimit)
	{
		CameraCompRelativeLocation.X = -XLimit;
	}
	
	if (CameraCompRelativeLocation.Y > YLimit)
	{
		CameraCompRelativeLocation.Y = YLimit;
	} else if (CameraCompRelativeLocation.Y < -YLimit)
	{
		CameraCompRelativeLocation.Y = -YLimit;
	}

	if (CameraCompRelativeLocation.Z > ZLimit)
	{
		CameraCompRelativeLocation.Z = ZLimit;
	} else if (CameraCompRelativeLocation.Z < -ZLimit)
	{
		CameraCompRelativeLocation.Z = -ZLimit;
	}
	
	CameraComp->SetRelativeLocation(UKismetMathLibrary::VInterpTo (CurrentLocation, CameraCompRelativeLocation, deltaTime, 5.f));
}

void AGameCamera::UpdateCameraRotation()
{
	FRotator NewCameraRotation = FRotator::ZeroRotator;
	if (PlayerCharacter != nullptr)
	{
		NewCameraRotation = (PlayerLocation-CameraComp->GetComponentLocation()).Rotation();
		CameraComp -> SetWorldRotation(NewCameraRotation);
	}

}


