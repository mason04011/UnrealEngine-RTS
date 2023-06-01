// Fill out your copyright notice in the Description page of Project Settings.



#include "TopDownCameraController.h"
#include "ResourceManager.h"
#include "Engine/World.h"
#include "GhostBuilding.h"
#include "WoodBuilding.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATopDownCameraController::ATopDownCameraController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//Attach our components
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);

	//Assign SpringArm class variables.
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-45.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = SpringArmLength;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	
	
}

// Called when the game starts or when spawned
void ATopDownCameraController::BeginPlay()
{
	Super::BeginPlay();


	//GetWorldTimerManager().SetTimer(ResourceProductionHandle, this, &ATopDownCameraController::Production, 30.0f, true);
	GetWorldTimerManager().SetTimer(HappinessTimerHandle, this, &ATopDownCameraController::HappinessCalculation, 300.0f, true);
}

// Called every frame
void ATopDownCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	


	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Cyan, FString::Printf(TEXT("TownHalls: %d"), NumberOfTownHalls));
	//Zooming in and out using the spring arm camera component
	{
		if(bZoomingIn)
		{
			ZoomInput = 10;
		}
		if(bZoomingOut)
		{
			ZoomInput = -10;
			
		}
		if(!bZoomingIn && !bZoomingOut)
		{
			ZoomInput = 0;
		}

		SpringArmLength += (ZoomInput * 400) * DeltaTime;
		SpringArmComp->TargetArmLength = SpringArmLength;
		bZoomingIn = false;
		bZoomingOut = false;
	}
	
	//Rotate our actor's yaw, which will turn our camera because we're attached to it
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += (RotateYaw.X * 10) * DeltaTime;
		SetActorRotation(NewRotation);
	}

	//Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!MovementInput.IsZero())
		{
			//Scale our movement input axis values by 100 units per second
			MovementInput = MovementInput.GetSafeNormal() * 600.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	

	{
		//PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	
		PlayerController->DeprojectMousePositionToWorld(MousePosition, MouseDirection);


		FCollisionQueryParams TraceParams(FName(TEXT("MouseTrace")), true, PlayerController);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredActor(GetOwner());

		
		TraceStart = MousePosition;
		TraceEnd = TraceStart + (MouseDirection * TraceDistance);  // Set the desired trace distance

		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
		{
			HitLocation = HitResult.ImpactPoint;
			HitRotation.Pitch = HitResult.ImpactPoint.Rotation().Pitch;

			ABuilding* BuildingClass = Cast<ABuilding>( HitResult.GetActor());
			
			if(BuildingClass)
			{
				bCanPlaceBuilding = false;
				GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Cyan, FString::Printf(TEXT("ActorName: %s"), *HitResult.GetActor()->GetName()));

			}else
			{
				bCanPlaceBuilding = true;
			}
			
		}
	}
	
}

void ATopDownCameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("PrimaryMouse", IE_Pressed,this, &ATopDownCameraController::PlaceBuilding);
	InputComponent->BindAction("SecondaryMouse", IE_Pressed,this, &ATopDownCameraController::StopBuildingPlacement);
	
	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed,this, &ATopDownCameraController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed,this, &ATopDownCameraController::ZoomOut);

	
	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("MoveVertically", this, &ATopDownCameraController::MoveForward);
	InputComponent->BindAxis("MoveHorizontally", this, &ATopDownCameraController::MoveRight);
	InputComponent->BindAxis("RotateYaw", this, &ATopDownCameraController::YawCamera);
}



/* ========================= functions to bind to the UI buttons in order to pick which building should be spawned in the SpawnBuilding funciton ========================= */

void ATopDownCameraController::BuildingSelectTownHall()
{
	StopBuildingPlacement();
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(GhostBuilding,HitLocation, HitRotation, SpawnParams);
	BuildingToSpawn = TownHall;
	WorkerCheck = 0;
	NumberOfTownHalls +=1;
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("TownHall is building to be spawned")));
}


void ATopDownCameraController::BuildingSelectSawMill()
{
	StopBuildingPlacement();
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(GhostBuilding,HitLocation, HitRotation, SpawnParams);
	BuildingToSpawn = Sawmill;
	WorkerCheck = 10;
	NumberOfSawMills += 1;
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf( TEXT("Sawmill is building to be spawned")));
}

void ATopDownCameraController::BuildingSelectLumberJack()
{
	StopBuildingPlacement();
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(GhostBuilding,HitLocation, HitRotation, SpawnParams);
	BuildingToSpawn = LumberJack;
	WorkerCheck = 10;
	NumberOfLumberJacks += 1;
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("lumberjack is building to be spawned")));
}

void ATopDownCameraController::BuildingSelectWorkerHouse()
{
	StopBuildingPlacement();
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(GhostBuilding,HitLocation, HitRotation, SpawnParams);
	NumberOfWorkerHouses += 1;
	WorkerCheck = 0;
	BuildingToSpawn = WorkerHouse;
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf( TEXT("workers house is building to be spawned")));
}

void ATopDownCameraController::BuildingSelectFarmHouse()
{
	StopBuildingPlacement();
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(GhostBuilding,HitLocation, HitRotation, SpawnParams);
	NumberOfFarmHouses += 1;
	WorkerCheck = 15;
	BuildingToSpawn = FarmHouse;
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf( TEXT("Farmhouse is building to be spawned")));
}

void ATopDownCameraController::BuildingSelectBrewery()
{
	StopBuildingPlacement();
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(GhostBuilding,HitLocation, HitRotation, SpawnParams);
	NumberOfBreweries += 1;
	WorkerCheck = 5;
	BuildingToSpawn = Brewery;
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf( TEXT("Brewery is building to be spawned")));
}

void ATopDownCameraController::BuildingSelectBakery()
{
	StopBuildingPlacement();
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(GhostBuilding,HitLocation, HitRotation, SpawnParams);
	NumberOfBakeries += 1;
	WorkerCheck = 5;
	BuildingToSpawn = Bakery;
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf( TEXT("Bakery is building to be spawned")));
}

/* ========================== Happienes Tax aplied to worker buildings ======================================================== */

void ATopDownCameraController::HappinessCalculation()
{
	UResourceManager* ResourceManager = Cast<UResourceManager>(GetWorld()->GetClass());
	if(ResourceManager)
	{
		if (ResourceManager->BreadDemandMet())
		{
			Morale += 5; //THIS NEEDS TO BE REDONE SO IT WILL WORK AS RIGHT NOW EVERY TIME HAPPINESS IS CALCULATED BREAD WILL GIVE +5
		}
	}


	if (Morale >= 100)
	{
		Happiness =  0.3f;
	}

	if (Morale >= 90)
	{
		Happiness = 0.25f;
	}

	if (Morale >= 80)
	{
		Happiness = 0.22f;
	}

	if (Morale >= 70)
	{
		Happiness = 0.2f;
	}

	if (Morale >= 60)
	{
		Happiness = 0.15f;
	}

	if(Morale <= 50)
	{
	Happiness = 0.1f;
	}
}

void ATopDownCameraController::Production()
{
	UResourceManager* ResourceManager = GetGameInstance()->GetSubsystem<UResourceManager>();
	ResourceManager->ProduceResources();
}

/*================================================================ Functions used by Action/Axis maps =======================================================*/

void ATopDownCameraController::MoveForward(float AxisValue)
{
	MovementInput.X = AxisValue;
}

void ATopDownCameraController::MoveRight(float AxisValue)
{
	MovementInput.Y = AxisValue;
}

void ATopDownCameraController::YawCamera(float AxisValue)
{
	RotateYaw.X = AxisValue;
}

void ATopDownCameraController::ZoomIn()
{
	bZoomingIn = true;
	
}

void ATopDownCameraController::ZoomOut()
{
	bZoomingOut = true;
}

void ATopDownCameraController::PlaceBuilding()
{
	UResourceManager* ResourceManager = GetGameInstance()->GetSubsystem<UResourceManager>();
	FActorSpawnParameters SpawnParams;
	if(bCanPlaceBuilding)
	{
		if(ResourceManager->GetWorkersAmount() >= WorkerCheck)
		{
			GetWorld()->SpawnActor<AActor>(BuildingToSpawn,HitLocation, HitRotation, SpawnParams);
			UE_LOG(LogTemp, Warning, TEXT("Placed"));
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Not Enough Workers"));
	}
}

void ATopDownCameraController::StopBuildingPlacement()
{
	BuildingToSpawn = nullptr;
	
	// Find all actors of class AGhostBuilding
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGhostBuilding::StaticClass(), FoundActors);

	// Iterate over the found actors and modify the boolean variable
	for (AActor* Actor : FoundActors)
	{
		AGhostBuilding* GhostBuildingActor = Cast<AGhostBuilding>(Actor);
		if (GhostBuildingActor != nullptr)
		{
			GhostBuildingActor->bDestroySelf = true;
		}
	}
}



