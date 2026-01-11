// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "BrainComponent.h"
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackPoint = CreateDefaultSubobject<USceneComponent>("AttackPoint");
	AttackPoint->SetupAttachment(RootComponent);

	CurrentIndex = -1;
}


// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::DestroyDelayed()
{
	Destroy();
}

float ABaseEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                             class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health-=DamageAmount;

	if (Health<=0)
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName("Ragdoll");
		if (auto MyController = Cast<AEnemyController>(GetController()))
		{
			MyController->GetBrainComponent()->StopLogic("Death");
			GetWorldTimerManager().SetTimer(TimerHandler,this, &ABaseEnemy::DestroyDelayed,2.0f,false);
		}
	}
	return Health;
}

void ABaseEnemy::OnattackHit()
{
	TArray<FOverlapResult> Results;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(AttackRadius);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// Debug sphere
	DrawDebugSphere(
		GetWorld(), 
		AttackPoint->GetComponentLocation(), 
		AttackRadius, 
		12, 
		FColor(0, 255, 255)
	);

	// Perform overlap
	bool bHit = GetWorld()->OverlapMultiByChannel(
		Results,
		AttackPoint->GetComponentLocation(),
		FQuat::Identity,
		ECC_GameTraceChannel1,
		CollisionShape,
		CollisionParams
	);

	for(FOverlapResult Result:Results){
		UGameplayStatics::ApplyDamage(Result.GetActor(), Damage, GetController(), this,UDamageType::StaticClass());
	}
}


FVector ABaseEnemy::GetNextPatrolPoint()
{
	// Ensure PatrolPath is valid
	if (!IsValid(PatrolPath))
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy '%s' has no PatrolPath assigned!"), *GetName());
		return GetActorLocation(); // fallback
	}

	USplineComponent* Spline = PatrolPath->GetSplineComponent();
	if (!IsValid(Spline))
	{
		UE_LOG(LogTemp, Error, TEXT("PatrolPath on '%s' has no valid spline!"), *GetName());
		return GetActorLocation();
	}

	int32 NumPoints = Spline->GetNumberOfSplinePoints();
	if (NumPoints == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Spline for '%s' has zero points!"), *GetName());
		return GetActorLocation();
	}
	
	if (CurrentIndex < 0)
	{
		CurrentIndex = 0;
	}
	
	CurrentIndex = (CurrentIndex + 1) % PatrolPath->GetSplineComponent()->GetNumberOfSplinePoints();
	return PatrolPath->GetSplineComponent()->GetLocationAtSplinePoint(CurrentIndex, ESplineCoordinateSpace::World);
}

void ABaseEnemy::PlayAttackMontage()
{
	PlayAnimMontage(Montage);
}

void ABaseEnemy::SetIsStrafing(bool bCond)
{
	bIsStrafing = bCond;
}


