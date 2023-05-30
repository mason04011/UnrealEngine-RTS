// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnBuildingWidget.h"
#include "Components/Button.h"
#include "TopDownCameraController.h"


bool USpawnBuildingWidget::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Super initialization failed"));
		return false;
	}

	TopDownPlayer = GetOwningPlayerPawn<ATopDownCameraController>();
	
	if (Button_TownHall)
	{
		Button_TownHall->OnClicked.AddDynamic(this, &USpawnBuildingWidget::TownHallButtonPressed);
	}

	if(Button_Worker)
	{
		Button_Worker->OnClicked.AddDynamic(this, &USpawnBuildingWidget::WorkerButtonPressed);
	}

	if(Button_Sawmill)
	{
		Button_Sawmill->OnClicked.AddDynamic(this, &USpawnBuildingWidget::SawmillButtonPressed);
	}

	if(Button_LumberJack)
	{
		Button_LumberJack->OnClicked.AddDynamic(this, &USpawnBuildingWidget::LumberJackButtonPressed);
	}


	return success;
}

void USpawnBuildingWidget::TownHallButtonPressed()
{
	TopDownPlayer->BuildingSelectTownHall();
	
	UE_LOG(LogTemp, Warning, TEXT("Button be buttoning"));
}

void USpawnBuildingWidget::WorkerButtonPressed()
{
	TopDownPlayer->BuildingSelectWorkerHouse();
}

void USpawnBuildingWidget::LumberJackButtonPressed()
{
	TopDownPlayer->BuildingSelectLumberJack();
}

void USpawnBuildingWidget::SawmillButtonPressed()
{
	TopDownPlayer->BuildingSelectSawMill();
}
