// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"


//Forward Declares
class UInputMappingContext;
class UInputAction;

//Delegate declaration 
DECLARE_DELEGATE_OneParam(FMovementDelegate, FVector2D);
DECLARE_DELEGATE_OneParam(FActionDelegate, bool);

UCLASS()

class NEUROHALLOWEEN_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = InputActions)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = InputActions)
	UInputAction* IAMove;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = InputActions)
	UInputAction* IAAction;

	FMovementDelegate MovementDelegate;

	FActionDelegate ActionDelegate;
	};
