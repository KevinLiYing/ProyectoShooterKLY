#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UStaticMeshComponent;
class ADamageProjectile;

UCLASS()
class SURVIVALSHOOTER_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADamageProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRange = 2000.f;

	FTimerHandle FireTimerHandle;

	UPROPERTY()
	AActor* PlayerActor;

	void FireAtPlayer();
};
