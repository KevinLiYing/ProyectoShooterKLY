#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "ProjectileShooterEnemy.generated.h"

class ADamageProjectile;

UCLASS()
class SURVIVALSHOOTER_API AProjectileShooterEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AProjectileShooterEnemy();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	TSubclassOf<ADamageProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float TimeBetweenShots = 2.f;

	FTimerHandle ShootTimerHandle;

	UPROPERTY()
	AActor* PlayerActor;

	virtual void BeginPlay() override;

	void ShootProjectile();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void ExitPlayMode();
};
