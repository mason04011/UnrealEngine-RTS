// Fill out your copyright notice in the Description page of Project Settings.

#include "WoodBuilding.h"

AWoodBuilding::AWoodBuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	BuildCost = 500;
}

void AWoodBuilding::Upkeep()
{
	ResourceManager->RemoveResource(TEXT("Money"), UpkeepCost);
}


void AWoodBuilding::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ProductionTimerHandle, this, &AWoodBuilding::ProduceResource_Implementation, 20.0f, true);
	GetWorldTimerManager().SetTimer(UpKeepTimerHandle, this, &AWoodBuilding::Upkeep, 300.0f, true);
	ResourceManager->RemoveResource(TEXT("Planks"), PlanksNeeded);
	ResourceManager->RemoveResource(TEXT("Workers"), WorkforceNeeded);
	ResourceManager->RemoveResource(TEXT("Money"), BuildCost);
	
}


bool AWoodBuilding::CanProduceResource_Implementation() const
{
	int32 Workers = ResourceManager->GetResourceAmount(TEXT("Workers"));

	if(Workers >= WorkforceNeeded)
	{
		return true;
	}
	return false;
}

void AWoodBuilding::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if(!GEngine)
	{
		return;
	}
	
if(!ResourceManager)
{

	ResourceManager = GetGameInstance()->GetSubsystem<UResourceManager>();
	if(!ResourceManager)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Black, FString::Printf(TEXT("No ResourceManager")));
		return;
	}
}
	



}

void AWoodBuilding::ProduceResource_Implementation()
{
	int32 TotalWood = ResourceManager->GetWoodAmount();
	if(TotalWood < ResourceManager->MaxResource)
	{
		ResourceManager->AddResource(TEXT("Wood"), 1);
		UE_LOG(LogTemp, Warning, TEXT("Producing wood resource!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wood output is full!"));
	}
}
