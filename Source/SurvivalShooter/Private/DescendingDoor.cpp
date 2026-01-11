#include "DescendingDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

ADescendingDoor::ADescendingDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh de la puerta
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SetRootComponent(DoorMesh);

	// Área de activación
	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));
	TriggerArea->SetupAttachment(RootComponent);
	TriggerArea->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &ADescendingDoor::OnTriggerBeginOverlap);
}

void ADescendingDoor::BeginPlay()
{
	Super::BeginPlay();

	DoorStart = DoorMesh->GetComponentLocation();
}

void ADescendingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFalling)
	{
		FVector TargetLocation = DoorStart - FVector(0,0,FallDistance);
		FVector NewLocation = FMath::VInterpConstantTo(DoorMesh->GetComponentLocation(), TargetLocation, DeltaTime, FallSpeed);
		DoorMesh->SetWorldLocation(NewLocation);
	}
}

void ADescendingDoor::ActivateDoor()
{
	bIsFalling = true;
}

void ADescendingDoor::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
											UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
											bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AShooterCharacter::StaticClass()) && !bBarrierCreated)
	{
		bBarrierCreated = true;

		if (BarrierClass)
		{
			FActorSpawnParameters SpawnParams;
			FVector SpawnLocation = OtherActor->GetActorLocation();
			FRotator SpawnRotation = FRotator::ZeroRotator;

			GetWorld()->SpawnActor<AActor>(BarrierClass, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
}
