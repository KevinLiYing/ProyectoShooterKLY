#include "CollectibleActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterCharacter.h"
#include "ShooterController.h"
#include "DoorController.h"
#include "Kismet/GameplayStatics.h"

ACollectibleActor::ACollectibleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleActor::OnOverlapBegin);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void ACollectibleActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
									   bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* Player = Cast<AShooterCharacter>(OtherActor);
	if (Player)
	{
		if (AShooterController* PC = Cast<AShooterController>(Player->GetController()))
		{
			PC->CollectItem();
		}

		TArray<AActor*> FoundDoors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorController::StaticClass(), FoundDoors);
		for (AActor* DoorActor : FoundDoors)
		{
			ADoorController* Door = Cast<ADoorController>(DoorActor);
			if (Door)
			{
				Door->AddCollectible();
			}
		}

		Destroy();
	}
}
