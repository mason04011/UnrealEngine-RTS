// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManager.h"

#include "TopDownCameraController.h"

UResourceManager::UResourceManager()
{
	//UE_LOG(LogTemp,Warning,TEXT("Resource Manager subSytem Created"))

		
}

bool UResourceManager::BreadDemandMet()
{
		ATopDownCameraController* TopDownPlayer = Cast<ATopDownCameraController>(GetWorld()->GetClass());
		int32 Workers = TopDownPlayer->NumberOfWorkerHouses * 8; //in the future buildings can be affected by items that may increase resident ammount and that a resident ammount variable will be here in place of the number

		BreadDemand = Workers * 0.25f;

		if(GetResourceAmount(TEXT("Bread")) >= BreadDemand)
		{
			RemoveResource(TEXT("Bread"), BreadDemand);
			return true;
		}
		
	return false;
		
}

void UResourceManager::AddResource(const FString& ResourceName, int32 Amount)
{
	FResource* Resource = Resources.Find(ResourceName);
	if (Resource)
	{
		Resource->Quantity += Amount;
	}
	else
	{
		FResource NewResource(ResourceName, Amount);
		Resources.Add(ResourceName, NewResource);
	}
}

void UResourceManager::RemoveResource(const FString& ResourceName, int32 Amount)
{
	FResource* Resource = Resources.Find(ResourceName);
	if (Resource)
	{
		Resource->Quantity -= Amount;
		if (Resource->Quantity <= 0)
		{
			Resource->Quantity = 0;
		}
	}
}

void UResourceManager::PreloadResources()
{
	AddResource(TEXT("Planks"), 100);
	AddResource(TEXT("Workers"), 25);
	AddResource(TEXT("Money"), 25000);
	AddResource(TEXT("Wood"), 0);
	AddResource(TEXT("Wheat"), 0);
	AddResource(TEXT("Bread"), 0);
	AddResource(TEXT("Beer"), 0);
}


// This function was going to replace the handling for resource production but, this will cause more problems for the future
void UResourceManager::ProduceResources()
{
	ATopDownCameraController* TopDownPlayer = Cast<ATopDownCameraController>(GetWorld()->GetClass());

	//LumberJack Building
	AddResource(TEXT("Wood"), TopDownPlayer->NumberOfLumberJacks);

	//SawMill Building
	RemoveResource(TEXT("Wood"), TopDownPlayer->NumberOfSawMills);
	AddResource(TEXT("Planks"),TopDownPlayer->NumberOfSawMills*3);

	//FarmHouse Building
	AddResource(TEXT("Wheat"), TopDownPlayer->NumberOfFarmHouses*4);

	//Brewery Building
	RemoveResource(TEXT("Wheat"), TopDownPlayer->NumberOfBreweries);
	AddResource(TEXT("Beer"), TopDownPlayer->NumberOfBreweries * 3);

	//Bakery Building
	RemoveResource(TEXT("Wheat"), TopDownPlayer->NumberOfBakeries);
	AddResource(TEXT("Wheat"), TopDownPlayer->NumberOfBakeries*2);
}

int32 UResourceManager::GetResourceAmount(const FString& ResourceName) const
{
	const FResource* Resource = Resources.Find(ResourceName);
	if (Resource)
	{
		return Resource->Quantity;
	}

	return 0;
}

int32 UResourceManager::GetWoodAmount() const
{
	const FResource* Resource = Resources.Find(TEXT("Wood"));
	if (Resource)
	{
		return Resource->Quantity;
	}

	return 0;
}

int32 UResourceManager::GetPlanksAmount() const
{
	const FResource* Resource = Resources.Find(TEXT("Planks"));
	if (Resource)
	{
		return Resource->Quantity;
	}

	return 0;
}

int32 UResourceManager::GetWorkersAmount() const
{
	const FResource* Resource = Resources.Find(TEXT("Workers"));
	if (Resource)
	{
		return Resource->Quantity;
	}

	return 0;
}

int32 UResourceManager::GetBalance() const
{
	const FResource* Resource = Resources.Find(TEXT("Money"));
	if (Resource)
	{
		return Resource->Quantity;
	}

	return 0;
}


