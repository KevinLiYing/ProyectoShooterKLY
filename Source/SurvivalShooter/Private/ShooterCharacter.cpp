// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "ShooterController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseEvent.h"
#include "Perception/AISense_Damage.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = MaxHealth;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;
	if(GetVelocity().Length() >= NoiseThreshold)
	{
		MakeNoise(1,this,GetActorLocation());
	}
}

void AShooterCharacter::Shoot()
{
	if (Timer >= TimeBetweenAttacks)
	{
		UGameplayStatics::SpawnEmitterAttached(Particles,GetMesh(),TEXT("Muzzle_01"));
		FVector ViewPointLocation;
		FRotator ViewPointDirection;
		FHitResult Hit;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		
		GetController()->GetPlayerViewPoint(ViewPointLocation,ViewPointDirection);

		FVector EndPoint = ViewPointLocation + ViewPointDirection.Vector() * AttackRange;

		DrawDebugLine(GetWorld(),ViewPointLocation,EndPoint,FColor::Red,false,2);
		if (GetWorld()->LineTraceSingleByChannel(Hit, ViewPointLocation,EndPoint, ECC_GameTraceChannel1,CollisionParams))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticles,Hit.Location);
			UAISense_Damage::ReportDamageEvent(GetWorld(), Hit.GetActor(),this,damage,GetActorLocation(),Hit.Location);
			UGameplayStatics::ApplyDamage(Hit.GetActor(),damage,GetController(),this, UDamageType::StaticClass());
		}
		Timer = 0;
	}
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	auto Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AShooterCharacter::Move);
	Input->BindAction(LookAction,ETriggerEvent::Triggered,this,&AShooterCharacter::Look);
	Input->BindAction(ShootAction,ETriggerEvent::Triggered,this,&AShooterCharacter::Shoot);
	//Input->BindAction(JumpAction,ETriggerEvent::Started,this,&ACharacter::Jump);

}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	auto MyController = Cast<AShooterController>(GetController());
	Health -= DamageAmount;
	MyController->UpdateHealth(Health);

	if (Health<=0)
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName("Ragdoll");
		
		MyController->PawnDeath();

	}
	return Health;
}

void AShooterCharacter::Move(const FInputActionValue& InputActionValue)
{
	FVector2D InputVector = InputActionValue.Get<FVector2D>();
	FRotator YawRotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector ForwardVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardVector,InputVector.Y);
	AddMovementInput(RightVector,InputVector.X);
}

void AShooterCharacter::Look(const FInputActionValue& InputActionValue)
{
	FVector2D MouseLook = InputActionValue.Get<FVector2D>();
	AddControllerPitchInput(-MouseLook.Y);
	AddControllerYawInput(MouseLook.X);
}

