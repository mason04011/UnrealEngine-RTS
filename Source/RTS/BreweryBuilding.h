// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "GameFramework/Actor.h"
#include "BreweryBuilding.generated.h"

UCLASS()
class RTS_API ABreweryBuilding : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreweryBuilding();

	void Upkeep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual bool CanProduceResource_Implementation() const override;
	virtual void ProduceResource_Implementation() override;

	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 PlanksNeeded = 10;
	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 WorkersNeeded = 5;

};
