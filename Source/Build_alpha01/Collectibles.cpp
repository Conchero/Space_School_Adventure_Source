// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectibles.h"
#include "Characters/MainCharacter.h"
#include "MasterPiece.h"

// Sets default values
ACollectibles::ACollectibles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACollectibles::BeginPlay()
{
	Super::BeginPlay();
	if (mesh != nullptr)
	{
		mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACollectibles::OnCollect);
	}
	TimerBeforeCollect_BP();
}

// Called every frame
void ACollectibles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectibles::OnCollect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (canCollect == true)
	{
		if (Cast<AMainCharacter>(OtherActor))
		{
			CollectEffect(Cast<AMainCharacter>(OtherActor));
			if (AMasterPiece* masterPiece = Cast<AMasterPiece>(this))
			{
			}
			else
			{
				Destroy();
			}
		}
	}
	
}

void ACollectibles::CollectEffect(class AMainCharacter* _character)
{
	PlayCollectSound();
	CollectEffect_BP(_character);
}

