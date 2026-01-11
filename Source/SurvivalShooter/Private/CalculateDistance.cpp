// Fill out your copyright notice in the Description page of Project Settings.


#include "CalculateDistance.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "EnemyController.h"
#include "EnemyStates.h"
#include "BehaviorTree/BlackboardComponent.h"

UCalculateDistance::UCalculateDistance()
{
	bNotifyTick = true;
}

void UCalculateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ABaseEnemy* MyPawn = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn()) ;
	AEnemyController* MyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	
	AActor* MyTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));

	FVector MyLocation = MyTarget->GetActorLocation();
	FVector TargetLocation = MyTarget->GetActorLocation();
	FVector TargetDistance = TargetLocation - MyLocation;
	float DistanceToTarget = TargetDistance.Size();

	if (DistanceToTarget > MinDistanceForStrafing)
	{
		MyPawn->SetIsStrafing(false);
		MyController->ChangeState(static_cast<uint8>(EEnemyStates::Chase));
	}
}
