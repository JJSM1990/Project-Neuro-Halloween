// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"
class ACustomPlayerController;
class USphereComponent;
UCLASS()
class NEUROHALLOWEEN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void Move(FVector2D InputDirection) const;
	UFUNCTION()
	void Action(bool bAction);
	UFUNCTION(BlueprintCallable, Category = CameraMovement)
	void NewRoom(FTransform NewCameraBaseTransform, UBoxComponent* newCameraLimits);

	FVector RoomForwardVector;
	FVector RoomRightVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InteractionLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USphereComponent* SphereComponent;

	ACustomPlayerController* GameController;
	
};
