// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkerBuilding.generated.h"

UCLASS()
class RTS_API AWorkerBuilding : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorkerBuilding();
	void Tax();
	void CalculateHappiness();

	float TaxBoost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	int32 WorkersProvided = 8;
	UPROPERTY(VisibleAnywhere)
	int32 PlanksNeeded = 10;

	UPROPERTY(VisibleAnywhere)
	float HappinessTax = 0.0f;

	UPROPERTY(VisibleAnywhere)
	int32 Happiness = 0.0f;

	UPROPERTY(VisibleAnywhere)
	float TaxPercentage = 0.1f + HappinessTax;

	UPROPERTY(VisibleAnywhere)
	bool bHasFood;

	UPROPERTY(VisibleAnywhere)
	bool bHasBooze;

};