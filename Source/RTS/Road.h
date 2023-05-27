// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

UCLASS()
class RTS_API ARoad : public AActor
{
	GENERATED_BODY()

public:
	ARoad();

	UFUNCTION(BlueprintCallable, Category = "Road")
	void ConnectBuilding(class ABuilding* Building);

private:
	TArray<class ABuilding*> ConnectedBuildings;
};
