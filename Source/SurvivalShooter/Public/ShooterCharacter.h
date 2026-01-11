// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SURVIVALSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float Health = 100;

	void Shoot();

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* ShootAction;
	
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 300;

	UPROPERTY(EditAnywhere)
	UParticleSystem* Particles;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitParticles;

	UPROPERTY()
	float TimeBetweenAttacks = 0.1f;

	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandler;



	float AttackRange = 800;
	float Timer;
	float damage = 10;
	
	float NoiseThreshold = 400;
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);

	

};
