// Fill out your copyright notice in the Description page of Project Settings.


#include "Bakery.h"

ABakery::ABakery()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BuildCost = 500;
	

}

// Called when the game starts or when spawned
void ABakery::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ProductionTimerHandle, this, &ABakery::ProduceResource_Implementation, 30.0f, true);
	ResourceManager->RemoveResource(TEXT("Planks"), PlanksNeeded);
	ResourceManager->RemoveResource(TEXT("Workers"), WorkersNeeded);
	ResourceManager->RemoveResource(TEXT("Money"), BuildCost);

	
}

// Called every frame
void ABakery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABakery::Upkeep()
{
	ResourceManager->RemoveResource(TEXT("Money"), UpkeepCost);
}

bool ABakery::CanProduceResource_Implementation() const
{
	return true;
}

void ABakery::ProduceResource_Implementation()
{

	int TotalBread = ResourceManager->GetResourceAmount(TEXT("Bread"));
	int TotalWheat = ResourceManager->GetResourceAmount(TEXT("Wheat"));
	if(CanProduceResource_Implementation())
	{
		if(TotalWheat > 0 && TotalBread < ResourceManager->MaxResource)
		{
			ResourceManager->RemoveResource(TEXT("Wheat"),1);
			ResourceManager->AddResource(TEXT("Bread"), 2);
		}		
	}



}