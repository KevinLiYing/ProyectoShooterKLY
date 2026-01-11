#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DescendingDoor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class SURVIVALSHOOTER_API ADescendingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADescendingDoor();

protected:

	// Mesh de la puerta
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* DoorMesh;

	// Área que activa la barrera invisible
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* TriggerArea;

	// Barrera invisible que se crea
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	TSubclassOf<AActor> BarrierClass;

	// Velocidad a la que baja la puerta
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	float FallSpeed = 200.f;

	// Distancia que la puerta debe bajar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	float FallDistance = 500.f;

	// Posición inicial de la puerta
	FVector DoorStart;

	// Flag para saber si la puerta empezó a bajar
	bool bIsFalling = false;

	// Flag para saber si la barrera se generó
	bool bBarrierCreated = false;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							   bool bFromSweep, const FHitResult& SweepResult);

public:

	// Función que activa la puerta (ej: llamada por el cubo)
	void ActivateDoor();
};
