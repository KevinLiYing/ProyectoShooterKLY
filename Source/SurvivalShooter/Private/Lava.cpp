#include "Lava.h"
#include "Components/BoxComponent.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

ALava::ALava()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALava::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ALava::OnOverlapEnd);
}

void ALava::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								 bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AShooterCharacter::StaticClass()))
	{
		OverlappingActor = OtherActor;
		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ALava::ApplyDamage, DamageInterval, true, 0.f);
	}
}

void ALava::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == OverlappingActor)
	{
		OverlappingActor = nullptr;
		GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	}
}

void ALava::ApplyDamage()
{
	if (OverlappingActor)
	{
		UGameplayStatics::ApplyDamage(OverlappingActor, Damage, nullptr, this, nullptr);

		AShooterCharacter* Player = Cast<AShooterCharacter>(OverlappingActor);
		if (Player && GEngine)
		{
			FString HealthText = FString::Printf(TEXT("Player Health: %f"), Player->Health);
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, HealthText);
		}
	}
}
