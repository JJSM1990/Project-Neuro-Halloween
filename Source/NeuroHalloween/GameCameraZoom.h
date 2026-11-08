// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCamera.h"
#include "GameCameraZoom.generated.h"

/**
 * 
 */
UCLASS()
class NEUROHALLOWEEN_API AGameCameraZoom : public AGameCamera
{
	GENERATED_BODY()
	
	virtual void Tick(float DeltaTime) override;
	void UpdateCameraZoom(float distanceToPlayerFromCamera, float minimumDistance, float maximumDistance,
	                      float maxFOVChange, float initialFOV, UCameraComponent* camera, float deltaTime );

	virtual void BeginPlay() override;

	float InitialFieldOfView;
	float DistanceToPlayerFromCamera;
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	float MaximumFieldOfViewLoss;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	float DistanceForMaximumZoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	float MinimumDistanceForZoom;
};
