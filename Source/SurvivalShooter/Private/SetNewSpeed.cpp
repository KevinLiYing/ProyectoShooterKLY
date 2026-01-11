// Fill out your copyright notice in the Description page of Project Settings.


#include "SetNewSpeed.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USetNewSpeed::USetNewSpeed()
{
	bNotifyBecomeRelevant = true; //inicio
	bNotifyTick = false;//actualizacion
	bNotifyCeaseRelevant = false;//final
}

void USetNewSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	// 1.Define en el .h una variable llamada speed
	// 2. En esete método has de poner al Pawn controlado por la Ia dicha velocidad, (max walk speed)
	OwnerComp.GetAIOwner()->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = Speed;
}
