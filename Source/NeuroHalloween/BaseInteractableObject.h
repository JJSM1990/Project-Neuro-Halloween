// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractableObject.h"
#include "BaseInteractableObject.generated.h"
class USceneComponent;
class UStaticMeshComponent;
class UWidgetComponent;
UCLASS()
class NEUROHALLOWEEN_API ABaseInteractableObject : public AActor, public IIInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ObjectInteraction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	USceneComponent* BaseRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	USceneComponent* MeshRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	UWidgetComponent* BaseWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectShake")
	float LateralDisplacement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectShake")
	float DisplacementReturnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectShake")
	float AngleShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectShake")
	float ShakeReturnSpeed;
	bool bLeftRight;
};
