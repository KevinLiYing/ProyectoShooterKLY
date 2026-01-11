// LavaVolume.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lava.generated.h"

class UBoxComponent;

UCLASS()
class SURVIVALSHOOTER_API ALava : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALava();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	// Daño que la lava aplica
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 20.f;

	// Tiempo entre cada tick de daño
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageInterval = 1.f;

	// Para llevar el control del timer
	FTimerHandle DamageTimerHandle;

	// Actor actual tocando la lava
	UPROPERTY()
	AActor* OverlappingActor;

	// Función que aplica daño
	void ApplyDamage();

	// Funciones para detectar entrada/salida del actor
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
};
