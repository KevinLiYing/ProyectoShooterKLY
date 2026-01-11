#include "ExplosiveCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DamageProjectile.h"
#include "Kismet/KismetSystemLibrary.h"

AExplosiveCharacter::AExplosiveCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AExplosiveCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AExplosiveCharacter::ShootProjectile()
{
	if (!ProjectileClass || !PlayerActor) return;

	FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 50.f);
	FRotator SpawnRotation = (PlayerActor->GetActorLocation() - SpawnLocation).Rotation();

	GetWorld()->SpawnActor<ADamageProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
}

float AExplosiveCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetHealth() <= 0)
	{
		SetActorTickEnabled(false);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AExplosiveCharacter::ExitPlayMode, 0.2f, false);
	}

	return DamageAmount;
}

void AExplosiveCharacter::ExitPlayMode()
{
#if WITH_EDITOR
	UKismetSystemLibrary::QuitEditor();
#endif
}
