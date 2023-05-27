// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TownHall.generated.h"

UCLASS()
class RTS_API ATownHall : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATownHall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
