#include "DamageArea.h"
#include "Components/BoxComponent.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

ADamageArea::ADamageArea()
{
	PrimaryActorTick.bCanEverTick = false;

	DamageZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageZone"));
	DamageZone->SetBoxExtent(FVector(200.f,200.f,50.f));
	DamageZone->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetRootComponent(DamageZone);

	DamageZone->OnComponentBeginOverlap.AddDynamic(this, &ADamageArea::OnOverlapBegin);
	DamageZone->OnComponentEndOverlap.AddDynamic(this, &ADamageArea::OnOverlapEnd);
}

void ADamageArea::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
}

void ADamageArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AShooterCharacter::StaticClass()))
	{
		OverlappingActor = OtherActor;
		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ADamageArea::ApplyDamage, DamageInterval, true, 0.f);
	}
}

void ADamageArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == OverlappingActor)
	{
		OverlappingActor = nullptr;
		GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	}
}

void ADamageArea::ApplyDamage()
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
