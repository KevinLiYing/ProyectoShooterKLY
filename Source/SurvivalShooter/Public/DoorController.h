#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorController.generated.h"

class UStaticMeshComponent;

UCLASS()
class SURVIVALSHOOTER_API ADoorController : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorController();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	float OpenDistance = 300.f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 200.f;

	void AddCollectible();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int32 CollectedCount = 0;
	bool bOpening = false;
	FVector StartLocation;
	FVector TargetLocation;
};
