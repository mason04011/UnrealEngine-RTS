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

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ABuilding::ABuilding()
{
	// Set default resource type provided by the building
	ProvidedResource = EResourceType::Invalid;

	BuildingBoundary = CreateDefaultSubobject<UStaticMeshComponent>("BoundaryMesh");
	BuildingBoundary->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f)); 
	BuildingBoundary->SetRenderCustomDepth(true); 
	BuildingBoundary->SetCustomDepthStencilValue(0); 

	BuildingFrame = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	BuildingFrame->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f)); 
	BuildingFrame->SetRenderCustomDepth(true); 
	BuildingFrame->SetCustomDepthStencilValue(1); 
	

	RootComponent = BuildingFrame;

	
}

bool ABuilding::CanProduceResource_Implementation() const
{

return false;
}

void ABuilding::ProduceResource_Implementation()
{
	
}
