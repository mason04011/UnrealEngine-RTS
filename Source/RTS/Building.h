// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ResourceType.h"
#include "ResourceManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

class UStaticMeshComponent;
UCLASS()
class RTS_API ABuilding : public AActor
{
	GENERATED_BODY()

protected:
	
	void BeginPlay();
	
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> BuildingFrame;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> BuildingBoundary;
	
	UPROPERTY()
	UResourceManager* ResourceManager;
	
	ABuilding();

	FTimerHandle ProductionTimerHandle;
	FTimerHandle TaxTimerHandle;
	FTimerHandle UpKeepTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	EResourceType ProvidedResource;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building")
	bool CanProduceResource() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building")
	void ProduceResource();

	UPROPERTY(VisibleAnywhere)
	int32 BuildCost;

	UPROPERTY(VisibleAnywhere)
	int32 UpkeepCost = BuildCost * 0.1f;

	UPROPERTY(VisibleAnywhere)
	float UpkeepModifier;
	

};
