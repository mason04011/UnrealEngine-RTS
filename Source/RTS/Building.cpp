// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"
#include "Components/StaticMeshComponent.h"

void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	ResourceManager = GetGameInstance()->GetSubsystem<UResourceManager>();
	if(ResourceManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("2"));
	}
	
}

ABuilding::ABuilding()
{
	// Set default resource type provided by the building
	ProvidedResource = EResourceType::Invalid;

	BuildingFrame = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	RootComponent = BuildingFrame;
}

bool ABuilding::CanProduceResource_Implementation() const
{

return false;
}

void ABuilding::ProduceResource_Implementation()
{
	
}
