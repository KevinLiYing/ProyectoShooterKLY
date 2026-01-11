// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <rapidjson/rapidjson.h>

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolPath.h" 
#include "BaseEnemy.generated.h"


UCLASS()
class SURVIVALSHOOTER_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();
	FORCEINLINE float GetHealth() const { return Health; }

	FVector GetNextPatrolPoint();
	void PlayAttackMontage();
	void SetIsStrafing(bool bCond);

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"));
	bool bIsStrafing = false;
	float Health = 30;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyDelayed();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
private:
	UPROPERTY(EditAnywhere)
	USceneComponent* AttackPoint;
	
	UPROPERTY(EditInstanceOnly)
	APatrolPath* PatrolPath;

	int32 CurrentIndex;
	
	float Damage =10;
	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandler;
	
	UPROPERTY(EditDefaultsOnly)
	float AttackRadius = 150;
	
	UFUNCTION(BlueprintCallable)
	void OnattackHit();

	

};
