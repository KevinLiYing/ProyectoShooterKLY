// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SetNewSpeed.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSHOOTER_API USetNewSpeed : public UBTService
{
	GENERATED_BODY()
public:
USetNewSpeed();
	UPROPERTY(EditAnywhere)
	float Speed = 200.0f;
protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
