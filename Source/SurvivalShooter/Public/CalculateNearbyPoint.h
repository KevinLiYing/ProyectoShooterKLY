// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CalculateNearbyPoint.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSHOOTER_API UCalculateNearbyPoint : public UBTTaskNode
{
	GENERATED_BODY()

	// Incluye el método correspondiente que se ejecuta cuando se ejecuta la tarea
	// Obten del blackboard la variable 'PointOfInterest'
	// Incluye una variable que se pueda editar de cualquier sitio que sea el radio de busqueda
	
	
	public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	float Radius = 5;

};
