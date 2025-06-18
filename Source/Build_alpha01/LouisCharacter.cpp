// Fill out your copyright notice in the Description page of Project Settings.



#include "LouisCharacter.h"
#include <Components/BoxComponent.h>
#include <Components/PrimitiveComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/AudioComponent.h>

// Sets default values
ALouisCharacter::ALouisCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	mesh->SetupAttachment(RootComponent);

	boxCollider = CreateDefaultSubobject<UBoxComponent>(FName("boxCollider"));
	boxCollider->SetupAttachment(RootComponent);

	audioComponent = CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALouisCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALouisCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timerShock -= DeltaTime;
	if (timerShock <= 0)
	{
	distToLouis = 100000000;
		TArray<AActor*> enemiesInZone;
		boxCollider->GetOverlappingActors(OUT enemiesInZone, AEnnemie::StaticClass());

		AEnnemie* enemyWithClosestRange = nullptr;
		for  (AActor* enemy : enemiesInZone)
		{
			if (Cast<AEnnemie>(enemy) != nullptr)
			{
				Cast<AEnnemie>(enemy)->louis = this;
				if (Cast<AEnnemie>(enemy)->GetDistanceWithLouis() <= distToLouis)
				{
					distToLouis = Cast<AEnnemie>(enemy)->GetDistanceWithLouis();
					enemyWithClosestRange = Cast<AEnnemie>(enemy);
				}
			}
		}

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("%f"), distToLouis));
		if (enemyWithClosestRange != nullptr)
		{
			FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), enemyWithClosestRange->GetActorLocation());
			BP_ATKImpulseEvent(enemyWithClosestRange,lookAtRotation);
			audioComponent->PitchMultiplier = 1 + (FMath::RandRange(-0.2f,0.2f));
			//enemyWithClosestRange->ShowElectricField();

		}
		timerShock = timerShockValue;

	}

}


