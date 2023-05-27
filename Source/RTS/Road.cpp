// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"


ARoad::ARoad()
{
	// ...
}

void ARoad::ConnectBuilding(ABuilding* Building)
{
	if (Building != nullptr)
	{
		ConnectedBuildings.Add(Building);
	}
}

