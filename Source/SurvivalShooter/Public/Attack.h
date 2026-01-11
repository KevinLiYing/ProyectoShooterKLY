#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Animation/AnimInstance.h"
#include "Attack.generated.h"

UCLASS()
class SURVIVALSHOOTER_API UAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAttack();

protected:
	// Main BT task execution
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;

	// Callback for when the attack montage ends
	UFUNCTION()
	void OnAttackEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	// Cached pointers to manage task lifecycle
	UBehaviorTreeComponent* CachedOwnerComp = nullptr;
	UAnimInstance* CachedAnimInstance = nullptr;
};
