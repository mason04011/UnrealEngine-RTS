// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManager.h"

UResourceManager::UResourceManager()
{
	//UE_LOG(LogTemp,Warning,TEXT("Resource Manager subSytem Created"))
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


