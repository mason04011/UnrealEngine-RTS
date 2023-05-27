// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

AGridManager::AGridManager()
{
	// initilize the RoadCells array
	RoadCells.SetNum(GridSizeX);

	for (int32 X = 0; X < GridSizeX; X++)
	{
		RoadCells[X].SetNum(GridSizeY, false);
	}
}

void AGridManager::InitializeGrid(int32 Rows, int32 Columns)
{
	Grid.Empty();

	for (int32 Row = 0; Row < Rows; ++Row)
	{
		TArray<class ABuilding*> Column;
		Column.Init(nullptr, Columns);
		Grid.Add(Column);
	}
}

void AGridManager::PlaceBuilding(int32 Row, int32 Column, ABuilding* Building)
{
	if (Building != nullptr && Grid.IsValidIndex(Row) && Grid[Row].IsValidIndex(Column))
	{
		Grid[Row][Column] = Building;
	}
}

bool AGridManager::IsRoadCell(int32 GridX, int32 GridY) const
{
	//checks if cell at x,y is a road
	if (GridX >= 0 && GridX < GridSizeX && GridY >= 0 && GridY < GridSizeY)
	{
		return RoadCells[GridX][GridY];
	}

	return false;
}

void AGridManager::UpdateResourceProduction()
{
	for (const TArray<class ABuilding*>& Row : Grid)
	{
		for (ABuilding* Building : Row)
		{
			if (Building != nullptr && Building->CanProduceResource())
			{
				Building->ProduceResource();
			}
		}
	}
}