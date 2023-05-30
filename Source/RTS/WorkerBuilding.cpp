// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerBuilding.h"

#include "TopDownCameraController.h"

// Sets default values
AWorkerBuilding::AWorkerBuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	BuildCost = 250;
}

void AWorkerBuilding::Tax()
{
	ATopDownCameraController* TopDownPlayer = Cast<ATopDownCameraController>(GetWorld()->GetClass());
	HappinessTax = TopDownPlayer->HappinessCalculation();
	ResourceManager->AddResource(TEXT("Money"), (BuildCost * HappinessTax));
}



// Called when the game starts or when spawned
void AWorkerBuilding::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ProductionTimerHandle, this, &AWorkerBuilding::Tax, 300.0f, true);

	ResourceManager->AddResource(TEXT("Workers"), WorkersProvided);
	ResourceManager->RemoveResource(TEXT("Planks"), PlanksNeeded);
	ResourceManager->RemoveResource(TEXT("Money"), BuildCost);
	UE_LOG(LogTemp, Warning, TEXT("Added Workers"));
	
}

// Called every frame
void AWorkerBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

