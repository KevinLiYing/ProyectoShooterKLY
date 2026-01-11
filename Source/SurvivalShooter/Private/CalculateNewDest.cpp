// Fill out your copyright notice in the Description page of Project Settings.


#include "CalculateNewDest.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UCalculateNewDest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* MyController = OwnerComp.GetAIOwner();
	APawn* EnemyPawn = MyController->GetPawn();

	if ( auto ShooterEnemy = Cast<ABaseEnemy>(EnemyPawn))
	{
		ShooterEnemy->GetNextPatrolPoint();
		OwnerComp.GetBlackboardComponent() -> SetValueAsVector("CurrentDestination", ShooterEnemy->GetNextPatrolPoint());
		return EBTNodeResult::Succeeded;
	}

	return  EBTNodeResult::Failed;
}
