// Fill out your copyright notice in the Description page of Project Settings.


#include "CalculateNearbyPoint.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UCalculateNearbyPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	FNavLocation NavLocation;
	FVector PointOfInterest = OwnerComp.GetBlackboardComponent()->GetValueAsVector("PointOfInterest");
/*
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	NavigationSystem->GetRandomReachablePointInRadius(PointOfInterest,Radius,NavLocation); 
*/
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("CurrentDestination", NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
