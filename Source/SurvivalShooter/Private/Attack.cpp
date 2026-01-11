#include "Attack.h"
#include "AIController.h"
#include "BaseEnemy.h"
#include "GameFramework/Character.h"

UAttack::UAttack()
{
	NodeName = TEXT("Attack");
	bCreateNodeInstance = true; // Critical: ensures each task has its own instance
}

EBTNodeResult::Type UAttack::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory
)
{
	CachedOwnerComp = &OwnerComp;

	AAIController* AI = OwnerComp.GetAIOwner();
	if (!AI)
	{
		return EBTNodeResult::Failed;
	}

	ABaseEnemy* Enemy = Cast<ABaseEnemy>(AI->GetPawn());
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}

	USkeletalMeshComponent* Mesh = Enemy->GetMesh();
	if (!Mesh)
	{
		return EBTNodeResult::Failed;
	}

	CachedAnimInstance = Mesh->GetAnimInstance();
	if (!CachedAnimInstance)
	{
		return EBTNodeResult::Failed;
	}

	// Bind the OnAttackEnded function to the montage ended delegate
	CachedAnimInstance->OnMontageEnded.AddDynamic(
		this,
		&UAttack::OnAttackEnded
	);

	// Play the attack montage on the enemy
	Enemy->PlayAttackMontage();

	// Task is in progress until montage ends
	return EBTNodeResult::InProgress;
}

void UAttack::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// Unbind to avoid duplicate calls or dangling references
	if (CachedAnimInstance)
	{
		CachedAnimInstance->OnMontageEnded.RemoveDynamic(
			this,
			&UAttack::OnAttackEnded
		);
	}

	// Finish the behavior tree task successfully
	if (CachedOwnerComp)
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
	}
}
