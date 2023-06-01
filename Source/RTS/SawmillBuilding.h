// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SawmillBuilding.generated.h"

UCLASS()
class RTS_API ASawmillBuilding : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASawmillBuilding();

	void Upkeep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	virtual bool CanProduceResource_Implementation() const override;
	virtual void ProduceResource_Implementation() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 PlanksNeeded = 10;
	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 WorkForceNeeded = 10;
	

};
