#include "DoorController.h"
#include "Components/StaticMeshComponent.h"

ADoorController::ADoorController()
{
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SetRootComponent(DoorMesh);
}

void ADoorController::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	TargetLocation = StartLocation + FVector(OpenDistance, 0, 0);
}

void ADoorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOpening)
	{
		FVector Current = GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(Current, TargetLocation, DeltaTime, OpenSpeed);
		SetActorLocation(NewLocation);
		if (FVector::Dist(NewLocation, TargetLocation) < 1.f)
		{
			bOpening = false;
		}
	}
}

void ADoorController::AddCollectible()
{
	CollectedCount++;
	if (CollectedCount >= 3)
	{
		bOpening = true;
	}
}
