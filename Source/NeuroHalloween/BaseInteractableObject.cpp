// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractableObject.h"

#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseInteractableObject::ABaseInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BaseRoot"));
	RootComponent = BaseRoot;
	
	MeshRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshRoot"));
	MeshRoot->SetupAttachment(RootComponent);
	
	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(MeshRoot);

	BaseWidget = CreateDefaultSubobject<UWidgetComponent>("BaseWidget");
	BaseWidget->SetupAttachment(BaseRoot);
}


// Called when the game starts or when spawned
void ABaseInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

// Called every frame
void ABaseInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MeshRootNewLocation = UKismetMathLibrary::VInterpTo(MeshRoot->GetRelativeLocation(), FVector::ZeroVector, DeltaTime, DisplacementReturnSpeed);
	MeshRoot->SetRelativeLocation(MeshRootNewLocation);
	FRotator MeshRootNewRotation = UKismetMathLibrary::RInterpTo(MeshRoot->GetRelativeRotation(), FRotator::ZeroRotator, DeltaTime, ShakeReturnSpeed);
	MeshRoot->SetRelativeRotation(MeshRootNewRotation);
	if(MeshRootNewLocation == FVector::ZeroVector && MeshRootNewRotation == FRotator::ZeroRotator)
	{
		SetActorTickEnabled(false);
	}
}

void ABaseInteractableObject::ObjectInteraction()
{
	UE_LOG(LogTemp, Warning,TEXT("Object Running"));
	if(!IsActorTickEnabled()) SetActorTickEnabled(true);
	if(bLeftRight)
	{
		bLeftRight = false;
		MeshRoot->SetRelativeRotation(FRotator(0,0,AngleShake));
		MeshRoot->SetRelativeLocation(FVector(LateralDisplacement,0,0));
	} else
	{
		bLeftRight = true;
		MeshRoot->SetRelativeRotation(FRotator(0,0,-AngleShake));
		MeshRoot->SetRelativeLocation(FVector(-LateralDisplacement,0,0));
	}
}


