// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "ShooterCharacter.h"
#include "GameFramework/PlayerController.h"
#include "ShooterController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSHOOTER_API AShooterController : public APlayerController
{
	GENERATED_BODY()
public:
	void DestroyDelayed();
	void PawnDeath();
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealth(float X);
	UPROPERTY()
	UUserWidget* HealthWidget;

	UPROPERTY(BlueprintReadWrite)

	int32 CollectedCount = 0;

	UFUNCTION()
	void CollectItem();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UUserWidget* HealthBarWidget;

};
