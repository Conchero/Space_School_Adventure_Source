// Fill out your copyright notice in the Description page of Project Settings.


#include "Canon.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include "Bullet.h"
#include "Components/AudioComponent.h"
// Sets default values
ACanon::ACanon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	mesh->SetupAttachment(RootComponent);
	spawner = CreateDefaultSubobject<USceneComponent>(FName("Spawner"));
	spawner->SetupAttachment(RootComponent);

	audioComponent= CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACanon::BeginPlay()
{
	Super::BeginPlay();
	timer = timerCooldown - timerOffset;
}

// Called every frame
void ACanon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Shoot(DeltaTime);
}

void ACanon::Shoot(float DeltaTime)
{
	if (bullet != nullptr)
	{
		timer -= DeltaTime;
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%f"), timer));

		if (timer <= 0)
		{
			/*	FRotator SpawnRotation = GetActorRotation();
				FVector SpawnPosition = spawner->GetComponentLocation()*/
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("shot")));
			GetWorld()->SpawnActor<ABullet>(bullet, spawner->GetComponentLocation(), GetActorRotation());
			timer = timerCooldown;
			PlayShootSound_BP();
		}
	}

}

