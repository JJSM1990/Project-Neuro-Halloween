// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractableObject.h"
#include "InteractableContainer.generated.h"

/**
 * 
 */
UCLASS()
class NEUROHALLOWEEN_API AInteractableContainer : public ABaseInteractableObject
{
	GENERATED_BODY()
	
	virtual void ObjectInteraction() override;
	
};
