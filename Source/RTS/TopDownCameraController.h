// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownCameraController.generated.h"

UCLASS()
class RTS_API ATopDownCameraController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATopDownCameraController();

	
	void MoveForward(float AxisValue);
	
	void MoveRight(float AxisValue);
	
	void YawCamera(float AxisValue);
	
	void ZoomIn();
	
	void ZoomOut();
	
	void PlaceBuilding();

	void StopBuildingPlacement();

	void BuildingSelectTownHall();
	
	void BuildingSelectSawMill();
	
	void BuildingSelectLumberJack();
	
	void BuildingSelectWorkerHouse();
	




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	float SpringArmLength = 600.0f;

	FVector MouseLocation;

	FVector2D MovementInput;
	
	FVector2D RotateYaw;
	
	float ZoomInput;
	
	bool bZoomingIn;
	
	bool bZoomingOut;

	FVector MousePosition;
	
	FViewport* Viewport;
	
	FHitResult HitResult;

	FVector HitLocation;

	FRotator HitRotation;
	
	FVector MouseDirection;
	
	FVector TraceStart;
	
	FVector TraceEnd;
	
	float TraceDistance = 300000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> LumberJack;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> Sawmill;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> WorkerHouse;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> TownHall;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> GhostBuilding;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> Floor;

	bool bCanPlaceBuilding;

	TSubclassOf<AActor> BuildingToSpawn;
	
};


