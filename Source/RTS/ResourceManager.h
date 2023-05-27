// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceManager.generated.h"


USTRUCT(BlueprintType)
struct FResource
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	FResource()
		: Name(TEXT("DefaultResource"))
		, Quantity(0)
	{
	}

	FResource(const FString& InName, int32 InQuantity)
		: Name(InName)
		, Quantity(InQuantity)
	{
	}
};
UCLASS()
class RTS_API UResourceManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UResourceManager();
	
	UFUNCTION(BlueprintCallable)
	void AddResource(const FString& ResourceName, int32 Amount);
	UFUNCTION(BlueprintCallable)
	void RemoveResource(const FString& ResourceName, int32 Amount);
	UFUNCTION(BlueprintCallable)
	void PreloadResources();
	UFUNCTION(BlueprintCallable)
	int32 GetResourceAmount(const FString& ResourceName) const;
	UFUNCTION(BlueprintCallable)
	int32 GetWoodAmount() const;
	UFUNCTION(BlueprintCallable)
	int32 GetPlanksAmount() const;
	UFUNCTION(BlueprintCallable)
	int32 GetWorkersAmount() const;
	UFUNCTION(BlueprintCallable)
	int32 GetBalance() const;
	UPROPERTY(VisibleAnywhere)
	int32 MaxResource = 100;

protected:


private:
	TMap<FString, FResource> Resources;
};
