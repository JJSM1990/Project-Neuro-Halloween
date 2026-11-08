// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCameraZoom.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"


void AGameCameraZoom::BeginPlay()
{
	Super::BeginPlay();
	InitialFieldOfView = CameraComp->FieldOfView;
	MaximumFieldOfViewLoss = 30;
	DistanceForMaximumZoom = 1000;
	MinimumDistanceForZoom = 600;
}

void AGameCameraZoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DistanceToPlayerFromCamera = (GetActorLocation() - PlayerLocation).Length();
	UpdateCameraZoom(DistanceToPlayerFromCamera, MinimumDistanceForZoom, DistanceForMaximumZoom, MaximumFieldOfViewLoss, InitialFieldOfView, CameraComp, DeltaTime);
}

void AGameCameraZoom::UpdateCameraZoom(float distanceToPlayerFromCamera, float minimumDistance, float maximumDistance, float maxFOVChange, float initialFOV, UCameraComponent* camera, float deltaTime)
{
	
	float distanceRatio;
	
	if (DistanceToPlayerFromCamera > minimumDistance)
	{
		distanceRatio = distanceToPlayerFromCamera / maximumDistance;
		if (distanceRatio > 1) distanceRatio = 1;
	} else
	{
		distanceRatio = 0;
	}
	
	float FOVLossTarget = maxFOVChange * distanceRatio;
	camera->FieldOfView = UKismetMathLibrary::FInterpTo(camera->FieldOfView, initialFOV-FOVLossTarget, deltaTime, 10 );

	
	
}