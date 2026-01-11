// Fill out your copyright notice in the Description page of Project Settings.


#include "SetFocusOnTarget.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

USetFocusOnTarget::USetFocusOnTarget()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = false;
	bNotifyCeaseRelevant = false;
}

void USetFocusOnTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	AAIController* Controller = OwnerComp.GetAIOwner();
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(Controller->GetPawn());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	Controller->SetFocus(Cast<AActor>(Blackboard->GetValueAsObject("Target")));
	Enemy->SetIsStrafing(true);
}

void USetFocusOnTarget::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	AAIController* Controller = OwnerComp.GetAIOwner();
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(Controller->GetPawn());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	Controller->ClearFocus(EAIFocusPriority::Gameplay);
	Enemy->SetIsStrafing(false);
}
