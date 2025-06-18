// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleCrate.h"
#include "DestructibleComponent.h"
#include "Characters/MainCharacter.h"
#include <Components/BoxComponent.h>
#include "Collectibles.h"

// Sets default values
ADestructibleCrate::ADestructibleCrate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	destructibleMesh = CreateDefaultSubobject<UDestructibleComponent>("destructibleMesh");
	destructibleMesh->SetupAttachment(RootComponent);
	boxCollider = CreateDefaultSubobject<UBoxComponent>("boxCollider");
	boxCollider->SetupAttachment(RootComponent);
	hitCollider = CreateDefaultSubobject<UBoxComponent>("hitCollider");
	hitCollider->SetupAttachment(RootComponent);
	audioComponent = CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADestructibleCrate::BeginPlay()
{
	Super::BeginPlay();
	boxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADestructibleCrate::OnCollision);
	hitCollider->OnComponentHit.AddUniqueDynamic(this, &ADestructibleCrate::OnCrateHit);
	nbChoiceCollectible = collectibleDrop.Num();
}

void ADestructibleCrate::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (isDestroyed == false)
	{
		if (Cast<AMainCharacter>(OtherActor) != nullptr)
		{
			OnCollisionEffect(Cast<AMainCharacter>(OtherActor));
		}
	}


}

void ADestructibleCrate::OnCollisionEffect(class AMainCharacter* _character)
{
	Destruction_BP(_character);
	CollectibleChoose();
	hitCollider->DestroyComponent(false);
	PlayDestroySound_BP();
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%d"), 1));

}

void ADestructibleCrate::OnCrateHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (isDestroyed == false)
	{
		if (Cast<AMainCharacter>(OtherActor) != nullptr && Cast<AMainCharacter>(OtherActor)->Attacking == true)
		{
			OnCollisionEffect(Cast<AMainCharacter>(OtherActor));
		}
	}
}

void ADestructibleCrate::CollectibleChoose()
{
	int randomNumber = FMath::Rand() % nbChoiceCollectible;
	
	if (collectibleDrop[randomNumber] != nullptr)
	{
		if (randomNumber <= GearDropChance)
		{
			int secondRandom = minGearDrop + FMath::Rand() % maxGearDrop;
			for (int i = 0; i < secondRandom; i++)
			{
				FVector randomOffset = FVector(FMath::RandRange(0.f, 40.f),FMath::RandRange(0.f, 40.f),0);
				ACollectibles* collectibleSpawned = GetWorld()->SpawnActor<ACollectibles>(collectibleDrop[randomNumber], (GetActorLocation() + (GetActorUpVector() * 50)) + randomOffset, FRotator::ZeroRotator);
			}
		}
		else
		{
			ACollectibles* collectibleSpawned = GetWorld()->SpawnActor<ACollectibles>(collectibleDrop[randomNumber], GetActorLocation() + (GetActorUpVector() * 50), FRotator::ZeroRotator);
		}
	
	}

}

// Called every frame
void ADestructibleCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

