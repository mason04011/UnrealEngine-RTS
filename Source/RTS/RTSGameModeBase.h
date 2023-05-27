// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GridManager.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Population")
	int32 Workers = 30;
	UPROPERTY(EditAnywhere, Category = "Population")
	int32 WorkersInUse = 0;
	UPROPERTY(EditAnywhere, Category = "Population")
	int32 FreeWorkers = Workers - WorkersInUse;
	UPROPERTY(EditAnywhere, Category = "Resources")
	int32 Wood = 50;
};
