// Fill out your copyright notice in the Description page of Project Settings.


#include "BreweryBuilding.h"

// Sets default values
ABreweryBuilding::ABreweryBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABreweryBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ProductionTimerHandle, this, &ABreweryBuilding::ProduceResource_Implementation, 30.0f, true);
	ResourceManager->RemoveResource(TEXT("Planks"), PlanksNeeded);
	ResourceManager->RemoveResource(TEXT("Workers"), WorkersNeeded);
	ResourceManager->RemoveResource(TEXT("Money"), BuildCost);
	
}

// Called every frame
void ABreweryBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABreweryBuilding::Upkeep()
{
	ResourceManager->RemoveResource(TEXT("Money"), UpkeepCost);
}

bool ABreweryBuilding::CanProduceResource_Implementation() const
{
	return true;
}

void ABreweryBuilding::ProduceResource_Implementation()
{

	int TotalBread = ResourceManager->GetResourceAmount(TEXT("Beer"));
	int TotalWheat = ResourceManager->GetResourceAmount(TEXT("Wheat"));
	if(CanProduceResource_Implementation())
	{
		if(TotalWheat > 0 && TotalBread < ResourceManager->MaxResource)
		{
			ResourceManager->RemoveResource(TEXT("Wheat"),1);
			ResourceManager->AddResource(TEXT("Beer"), 4);
		}		
	}



}

