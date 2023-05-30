// Fill out your copyright notice in the Description page of Project Settings.


#include "SawmillBuilding.h"

// Sets default values
ASawmillBuilding::ASawmillBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASawmillBuilding::Upkeep()
{
	ResourceManager->RemoveResource(TEXT("Money"), UpkeepCost);
}

// Called when the game starts or when spawned
void ASawmillBuilding::BeginPlay()
{
	Super::BeginPlay();

	BuildCost = 500;

	GetWorldTimerManager().SetTimer(ProductionTimerHandle, this, &ASawmillBuilding::ProduceResource_Implementation, 20.0f, true);
	GetWorldTimerManager().SetTimer(UpKeepTimerHandle, this, &ASawmillBuilding::Upkeep, 300.0f, true);
	ResourceManager->RemoveResource(TEXT("Planks"), PlanksNeeded);
	ResourceManager->RemoveResource(TEXT("Workers"), WorkersNeeded);
	ResourceManager->RemoveResource(TEXT("Money"), BuildCost);
	
}

bool ASawmillBuilding::CanProduceResource_Implementation() const
{
	int32 Workers = ResourceManager->GetResourceAmount(TEXT("Workers"));

	if(Workers >= WorkersNeeded)
	{
		return true;
	}
	return false;
}

void ASawmillBuilding::ProduceResource_Implementation()
{
	int32 TotalWood = ResourceManager->GetResourceAmount(TEXT("Wood"));
	int32 TotalPlanks = ResourceManager->GetResourceAmount(TEXT("Planks"));
	if(TotalWood > 0)
	{
		if(TotalPlanks < ResourceManager->MaxResource -3 )
		{
			ResourceManager->RemoveResource(TEXT("Wood"), 1);
			ResourceManager->AddResource(TEXT("Planks"), 3);
			UE_LOG(LogTemp, Warning, TEXT("Producing plank resource!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Plank output is full!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of Wood to mill!"));
	}


}

// Called every frame
void ASawmillBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

