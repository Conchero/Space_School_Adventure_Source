// Fill out your copyright notice in the Description page of Project Settings.


#include "CrushingPillar.h"
#include <Components/BoxComponent.h>
#include "Characters/MainCharacter.h"
#include "LD/RespawnableObject.h"

// Sets default values
ACrushingPillar::ACrushingPillar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	stickMesh = CreateDefaultSubobject<UStaticMeshComponent>("stickMesh");
	stickMesh->SetupAttachment(RootComponent);
	supportMesh = CreateDefaultSubobject<UStaticMeshComponent>("supportMesh");
	supportMesh->SetupAttachment(RootComponent);
	spikeMesh = CreateDefaultSubobject<UStaticMeshComponent>("spikeMesh");
	spikeMesh->SetupAttachment(RootComponent);

	damageBoxCollider = CreateDefaultSubobject<UBoxComponent>("damageBoxCollider");
	damageBoxCollider->SetupAttachment(spikeMesh);
	audioComponent = CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);
	//rightBoxCollider = CreateDefaultSubobject<UBoxComponent>("rightBoxCollider");
	//rightBoxCollider->SetupAttachment(RootComponent);
	//backBoxCollider = CreateDefaultSubobject<UBoxComponent>("backBoxCollider");
	//backBoxCollider->SetupAttachment(RootComponent);
	//frontBoxCollider = CreateDefaultSubobject<UBoxComponent>("frontBoxCollider");
	//frontBoxCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACrushingPillar::BeginPlay()
{
	Super::BeginPlay();
	basePos = GetActorLocation();

	damageBoxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACrushingPillar::OnCollisionDetected);

	meshToMove.Add(stickMesh);
	meshToMove.Add(spikeMesh);
}

// Called every frame
void ACrushingPillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CrushingPillarMovement(DeltaTime);
}

void ACrushingPillar::CrushingPillarMovement(float DeltaTime)
{
	if (crush)
	{

		if (GetActorLocation().Z >= basePos.Z - finalZValue)
		{
			SetActorLocation(FVector(basePos.X, basePos.Y, GetActorLocation().Z - (DeltaTime * speedCrush)));
		}
		else
		{
			PlayCrushSound_BP();
			crush = false;
		}


	}
	else
	{

		if (GetActorLocation().Z <= basePos.Z)
		{
			SetActorLocation(FVector(basePos.X, basePos.Y, GetActorLocation().Z + (DeltaTime * speedPullOut)));
		}
		else
		{
			crush = true;
		}

	}
}

void ACrushingPillar::OnCollisionDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (crush)
	{

		if (Cast<AMainCharacter>(OtherActor) != nullptr)
		{
			CollisionEffect(Cast<AMainCharacter>(OtherActor));
		}
		if (Cast<ARespawnableObject>(OtherActor) != nullptr)
		{
			//ARespawnableObject* actor = Cast<ARespawnableObject>(OtherActor);
			//actor->RespawnObject();
		}
	}

}

void ACrushingPillar::CollisionEffect(AMainCharacter* _character)
{
	_character->RemoveLife(1, false, _dirLaunch);
}

