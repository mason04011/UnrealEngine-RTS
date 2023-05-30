#pragma once

#include "CoreMinimal.h"
#include "TopDownCameraController.h"
#include "Blueprint/UserWidget.h"
#include "SpawnBuildingWidget.generated.h"


class ATopDownCameraController;
UCLASS()
class RTS_API USpawnBuildingWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	

	ATopDownCameraController* TopDownPlayer;

protected:
	
	virtual bool Initialize() override;

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_TownHall;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Worker;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Sawmill;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_LumberJack;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_FarmHouse;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Bakery;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Brewery;

private:
	
	UFUNCTION()
	void TownHallButtonPressed();

	UFUNCTION()
	void WorkerButtonPressed();

	UFUNCTION()
	void LumberJackButtonPressed();

	UFUNCTION()
	void SawmillButtonPressed();

	UFUNCTION()
	void FarmHouseButtonPressed();

	UFUNCTION()
	void BakeryButtonPressed();

	UFUNCTION()
	void BreweryButtonPressed();
};