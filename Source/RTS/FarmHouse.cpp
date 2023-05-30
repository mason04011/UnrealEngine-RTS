// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmHouse.h"

// Sets default values
AFarmHouse::AFarmHouse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BuildCost = 1000;
	

}

// Called when the game starts or when spawned
void AFarmHouse::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ProductionTimerHandle, this, &AFarmHouse::ProduceResource_Implementation, 60.0f, true);
	ResourceManager->RemoveResource(TEXT("Planks"), PlanksNeeded);
	ResourceManager->RemoveResource(TEXT("Workers"), WorkersNeeded);
	ResourceManager->RemoveResource(TEXT("Money"), BuildCost);

	
}

// Called every frame
void AFarmHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFarmHouse::Upkeep()
{
	ResourceManager->RemoveResource(TEXT("Money"), UpkeepCost);
}

bool AFarmHouse::CanProduceResource_Implementation() const
{
	return true;
}

void AFarmHouse::ProduceResource_Implementation()
{
	int TotalWheat = ResourceManager->GetResourceAmount(TEXT("Wheat"));
	
	if(CanProduceResource_Implementation() && TotalWheat < ResourceManager->MaxResource)
	{
		ResourceManager->AddResource(TEXT("Wheat"), 4);
	}


}

