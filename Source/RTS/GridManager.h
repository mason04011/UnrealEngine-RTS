// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

UCLASS()
class RTS_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	AGridManager();

	bool IsRoadCell(int32 GridX, int32 GridY) const;
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void InitializeGrid(int32 Rows, int32 Columns);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void PlaceBuilding(int32 Row, int32 Column, class ABuilding* Building);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void UpdateResourceProduction();

	UPROPERTY(EditAnywhere)
	float CellSize = 100.0f; 
private:
	TArray<TArray<class ABuilding*>> Grid;
	
	TArray<TArray<bool>> RoadCells; // 2D array to store road cell information

	UPROPERTY(EditAnywhere)
	int32 GridSizeX = 10; // Number of cells in X-axis
	UPROPERTY(EditAnywhere)
	int32 GridSizeY = 10; // Number of cells in Y-axis

};
