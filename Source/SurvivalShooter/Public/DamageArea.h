#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageArea.generated.h"

class UBoxComponent;

UCLASS()
class SURVIVALSHOOTER_API ADamageArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageArea();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* DamageZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageInterval = 1.f;

	FTimerHandle DamageTimerHandle;

	UPROPERTY()
	AActor* OverlappingActor;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ApplyDamage();

	// Tiempo de vida del área de daño
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float LifeTime = 5.f;

	virtual void BeginPlay() override;
};
