#include "Turret.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DamageProjectile.h"
#include "TimerManager.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMesh);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurret::FireAtPlayer, FireRate, true, 0.f);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerActor)
	{
		FVector ToPlayer = PlayerActor->GetActorLocation() - GetActorLocation();
		FRotator LookRotation = ToPlayer.Rotation();
		LookRotation.Pitch = 0;
		LookRotation.Roll = 0;
		SetActorRotation(LookRotation);
	}
}

void ATurret::FireAtPlayer()
{
	if (!PlayerActor || !ProjectileClass) return;

	FVector ToPlayer = PlayerActor->GetActorLocation() - GetActorLocation();
	if (ToPlayer.Size() > FireRange) return;

	FVector SpawnLocation = GetActorLocation() + FVector(0,0,50.f);
	FRotator SpawnRotation = ToPlayer.Rotation();

	GetWorld()->SpawnActor<ADamageProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
}
