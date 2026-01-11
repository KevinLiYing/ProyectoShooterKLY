#include "ProjectileShooterEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "DamageProjectile.h"
#include "Kismet/KismetSystemLibrary.h"

AProjectileShooterEnemy::AProjectileShooterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileShooterEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (ProjectileClass)
	{
		GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AProjectileShooterEnemy::ShootProjectile, TimeBetweenShots, true);
	}
}

void AProjectileShooterEnemy::ShootProjectile()
{
	if (!ProjectileClass || !PlayerActor) return;

	FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 50.f);
	FRotator SpawnRotation = (PlayerActor->GetActorLocation() - SpawnLocation).Rotation();

	GetWorld()->SpawnActor<ADamageProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
}

float AProjectileShooterEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetHealth() <= 0)
	{
		GetWorldTimerManager().ClearTimer(ShootTimerHandle);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AProjectileShooterEnemy::ExitPlayMode, 0.1f, false);
	}

	return DamageAmount;
}

void AProjectileShooterEnemy::ExitPlayMode()
{
#if WITH_EDITOR
	UKismetSystemLibrary::QuitEditor();
#endif
}
