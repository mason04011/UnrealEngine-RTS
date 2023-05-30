// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostBuilding.h"

#include "TopDownCameraController.h"

// Sets default values
AGhostBuilding::AGhostBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bGhostBuildingActive = true;

}

void AGhostBuilding::SetGhostBuildingActive()
{
	bGhostBuildingActive = true;
}

void AGhostBuilding::SetGhostBuildingInactive()
{
	bGhostBuildingActive = false;
}

void AGhostBuilding::DestroySelf()
{
	if(bDestroySelf)
	{
		Destroy();
	}
}

// Called when the game starts or when spawned
void AGhostBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		Viewport = PlayerController->GetLocalPlayer()->ViewportClient->Viewport;
		
	}



	
}

// Called every frame
void AGhostBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	if(bGhostBuildingActive)
	{
		//PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	
		PlayerController->DeprojectMousePositionToWorld(MousePosition, MouseDirection);


		FCollisionQueryParams TraceParams(FName(TEXT("MouseTrace")), true, PlayerController);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredActor(GetOwner());
		
		TraceStart = MousePosition;
		TraceEnd = TraceStart + (MouseDirection * TraceDistance);  // Set the desired trace distance

		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
		{
			FVector HitLocation = HitResult.ImpactPoint;
			if(ABuilding* BuildingClass = Cast<ABuilding>( HitResult.GetActor()))
			{
				return;
			}else
			{
				SetActorLocation(HitLocation);
			}
		}
	}

	DestroySelf();

}

