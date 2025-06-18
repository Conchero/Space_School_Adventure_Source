// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps.h"
#include <Components/BoxComponent.h>
#include <Components/PrimitiveComponent.h>
#include <Components/SceneComponent.h>
#include "Characters/MainCharacter.h"

// Sets default values
ATraps::ATraps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//emptyParent = CreateDefaultSubobject<USceneComponent>(FName("Parent"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	mesh->SetupAttachment(RootComponent);
	boxCollider = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	boxCollider->SetupAttachment(RootComponent);
	boxCollider->SetRelativeLocation(FVector(0,0,0));
	loopAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("loopAudioComponent"));
	loopAudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATraps::BeginPlay()
{
	Super::BeginPlay();
	if (boxCollider != nullptr)
	{
		boxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATraps::OnPlayerCollisionEnter);
	}
}


void ATraps::OnPlayerCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Activated")));
		activated = true;
		Cast<AMainCharacter>(OtherActor)->RemoveLife(1,stun,launchCharacterDir);
		Cast<AMainCharacter>(OtherActor)->PlayImpactSound_BP();
	}

}

// Called every frame
void ATraps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

