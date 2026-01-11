#include "ShooterController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

void AShooterController::DestroyDelayed()
{
	if (HasAuthority())
	{
		if (AGameModeBase* GM = GetWorld()->GetAuthGameMode())
		{
			GM->RestartPlayer(this);
		}
	}
}

void AShooterController::PawnDeath()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		ControlledPawn->SetLifeSpan(3.0f);
	}

	UnPossess();

	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&AShooterController::DestroyDelayed,
		3.0f,
		false
	);
}


void AShooterController::BeginPlay()
{
	Super::BeginPlay();

	// UI should only exist on local player controllers
	if (IsLocalController() && HealthBar)
	{
		HealthWidget = CreateWidget<UUserWidget>(this, HealthBar);
		if (HealthWidget)
		{
			HealthWidget->AddToViewport();
		}
	}

	// Enhanced Input ONLY for local players
	if (IsLocalController())
	{
		if (ULocalPlayer* LP = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* System =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
			{
				System->AddMappingContext(MappingContext, 0);
			}
		}
	}
}

void AShooterController::CollectItem()
{
	CollectedCount++;
	if (CollectedCount >= 6)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, true);
	}
}
