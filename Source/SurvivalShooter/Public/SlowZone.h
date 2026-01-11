// SlowZone.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlowZone.generated.h"

class UBoxComponent;

UCLASS()
class SURVIVALSHOOTER_API ASlowZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlowZone();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	// Porcentaje de reducción de velocidad (ej: 0.2 = 20%)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slow")
	float SlowPercentage = 0.2f;

	// Para guardar la velocidad original del jugador
	UPROPERTY()
	float OriginalSpeed;

	// Funciones para detectar entrada y salida
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
