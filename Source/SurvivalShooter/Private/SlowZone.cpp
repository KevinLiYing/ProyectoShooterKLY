// SlowZone.cpp
#include "SlowZone.h"
#include "Components/BoxComponent.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASlowZone::ASlowZone()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASlowZone::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASlowZone::OnOverlapEnd);
}

void ASlowZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AShooterCharacter::StaticClass()))
	{
		AShooterCharacter* Player = Cast<AShooterCharacter>(OtherActor);
		if (Player)
		{
			OriginalSpeed = Player->GetCharacterMovement()->MaxWalkSpeed;
			Player->GetCharacterMovement()->MaxWalkSpeed *= (1.0f - SlowPercentage);
		}
	}
}

void ASlowZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(AShooterCharacter::StaticClass()))
	{
		AShooterCharacter* Player = Cast<AShooterCharacter>(OtherActor);
		if (Player)
		{
			Player->GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed;
		}
	}
}
