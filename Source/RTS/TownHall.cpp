// Fill out your copyright notice in the Description page of Project Settings.


#include "TownHall.h"

// Sets default values
ATownHall::ATownHall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATownHall::BeginPlay()
{
	Super::BeginPlay();
	ResourceManager->PreloadResources();
	
}

// Called every frame
void ATownHall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Black, FString::Printf(TEXT("Wood: %i"),ResourceManager->GetResourceAmount(TEXT("Wood"))));
	GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Black, FString::Printf(TEXT("Planks: %i"),ResourceManager->GetResourceAmount(TEXT("Planks"))));
	GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Black, FString::Printf(TEXT("Workers: %i"),ResourceManager->GetResourceAmount(TEXT("Workers"))));

}

