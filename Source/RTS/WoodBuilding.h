// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Building.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WoodBuilding.generated.h"

UCLASS()
class RTS_API AWoodBuilding : public ABuilding
{
	GENERATED_BODY()

public:

	void BeginPlay();
	
	AWoodBuilding();

	void Upkeep();
	
	virtual bool CanProduceResource_Implementation() const override;
	virtual void ProduceResource_Implementation() override;

	virtual void Tick(float DeltaTime) override;

private:
	

	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 WorkforceNeeded = 10;
	UPROPERTY(VisibleAnywhere, Category = "Resources")
	int32 PlanksNeeded = 5;
	


};
