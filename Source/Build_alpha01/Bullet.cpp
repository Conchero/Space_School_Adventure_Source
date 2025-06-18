// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Characters/MainCharacter.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/BoxComponent.h>
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	mesh->SetupAttachment(RootComponent);
	boxCollider = CreateDefaultSubobject<UBoxComponent>(FName("boxCollider"));
	boxCollider->SetupAttachment(RootComponent);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	projectileMovementComponent->bInitialVelocityInLocalSpace = true;
	projectileMovementComponent->InitialSpeed = speed;
	projectileMovementComponent->MaxSpeed = speed;
	projectileMovementComponent->ProjectileGravityScale = 0;
	InitialLifeSpan = lifeSpan;

    audioComponent = CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABullet::OnCollision);
	boxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABullet::OnJumpCollision);
	projectileMovementComponent->bInitialVelocityInLocalSpace = true;
	projectileMovementComponent->InitialSpeed = speed;
	projectileMovementComponent->MaxSpeed = speed;
	projectileMovementComponent->ProjectileGravityScale = 0;
	InitialLifeSpan = lifeSpan;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::LaunchBullet()
{

}

void ABullet::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (Cast<AMainCharacter>(OtherActor) != nullptr )
	//{
	//	Cast<AMainCharacter>(OtherActor)->RemoveLife(damage,true,launchCharacterDir);
	//	Cast<AMainCharacter>(OtherActor)->PlayImpactSound_BP();
	//	PlayExplodeSound_BP();
	//}
	//if (Cast<ABullet>(OtherActor) == nullptr && Cast<ALouisCharacter>(OtherActor) == nullptr)
	//{
	//	PlayExplodeSound_BP();
	//	Destroy();
	//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player")));
	//}
}

void ABullet::OnJumpCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		Cast<AMainCharacter>(OtherActor)->GetCharacterMovement()->Launch(GetActorUpVector() * 1000);
		PlayExplodeSound_BP();
		Destroy();
	}

}

