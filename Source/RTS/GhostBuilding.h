// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TopDownCameraController.h"
#include "Building.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GhostBuilding.generated.h"

UCLASS()
class RTS_API AGhostBuilding : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostBuilding();

	void SetGhostBuildingActive();
	void SetGhostBuildingInactive();
	void DestroySelf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bGhostBuildingActive;
	
	FVector MousePosition;
	
	FViewport* Viewport;
	
	FHitResult HitResult;
	
	FVector MouseDirection;
	
	FVector TraceStart;
	
	FVector TraceEnd;
	
	float TraceDistance = 300000.f;

	UPROPERTY(BlueprintReadWrite)
	bool bDestroySelf = false;

};
