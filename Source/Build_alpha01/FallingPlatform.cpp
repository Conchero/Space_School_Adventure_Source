// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingPlatform.h"
#include "Components/BoxComponent.h"
#include <Engine/StaticMeshActor.h>
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "Math/Vector.h"
#include "Characters/MainCharacter.h"

#define VALUE_TIMER_BEFORE_FALL 1.5f;
#define VALUE_TIMER_BEFORE_RESPAWN 3.f;

// Sets default values
AFallingPlatform::AFallingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerOnPlatform = false;
	platformFalling = false;
	timerBeforeFall = VALUE_TIMER_BEFORE_FALL;
	speed = 500;
	distance = 200;
	readyToRespawn = false;
	timerBeforeRespawn = VALUE_TIMER_BEFORE_RESPAWN;
	speedShaking = 100;
	shakingOffset = 1;
	shakeRight = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));

	audioComponent = CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);


	boxCollider = CreateDefaultSubobject<UBoxComponent>(FName("boxCollider"));
	boxCollider->SetupAttachment(RootComponent);

	platformCollider = CreateDefaultSubobject<UBoxComponent>(FName("platformCollider "));
	platformCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFallingPlatform::BeginPlay()
{
	Super::BeginPlay();

	basePos = new FVector(GetActorLocation());

	//boxCollider = this->FindComponentByClass<UBoxComponent>();

	staticMesh = this->FindComponentByClass<UStaticMeshComponent>();
	baseRot = new FRotator(staticMesh->GetRelativeRotation());
	if (boxCollider != nullptr)
	{
		boxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AFallingPlatform::FallingBehaviourEnter);
		boxCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &AFallingPlatform::FallingBehaviourExit);
	}

}





void AFallingPlatform::FallingBehaviourEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		if (platformFalling == false)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), timerBeforeRespawn));

			playerOnPlatform = true;
		
		}
	}

}

void AFallingPlatform::FallingBehaviourExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (platformFalling == false)
	//{
	//	SetActorRotation(FRotator(baseRot->Pitch, baseRot->Yaw, baseRot->Roll));
	//	playerOnPlatform = false;
	//	timerBeforeFall = VALUE_TIMER_BEFORE_FALL;
	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("out")));
	//}

}

void AFallingPlatform::ResetValues()
{
	speed = 500;
	distance = 200;
	playerOnPlatform = false;
	readyToRespawn = false;
	platformFalling = false;
	timerBeforeFall = VALUE_TIMER_BEFORE_FALL;
	timerBeforeRespawn = VALUE_TIMER_BEFORE_RESPAWN;
	SetActorLocation(FVector(basePos->X, basePos->Y, basePos->Z));
	SetActorHiddenInGame(false);
	platformCollider->SetCollisionProfileName(TEXT("BlockAll"));

}

// Called every frame
void AFallingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (playerOnPlatform && platformFalling == false)
	{
		timerBeforeFall -= DeltaTime;

		if (timerBeforeFall <= 0)
		{
			if (playFallSound == false)
			{
				PlayFallSound_BP();
				playFallSound = true;
			}
			staticMesh->SetRelativeRotation(FRotator(baseRot->Pitch, baseRot->Yaw, baseRot->Roll));
			platformFalling = true;
			if (playShakeSound == true)
			{
				StopShakingSound_BP();
				playShakeSound = false;
			}
		}
		else
		{
			if (playShakeSound == false)
			{
				PlayShakingSound_BP();
				playShakeSound = true;
			}
			if (shakeRight == false)
			{
				if (staticMesh->GetRelativeRotation().Pitch > baseRot->Pitch - shakingOffset)
				{
					staticMesh->SetRelativeRotation(FRotator(staticMesh->GetRelativeRotation().Pitch - (DeltaTime * speedShaking), staticMesh->GetRelativeRotation().Yaw, staticMesh->GetRelativeRotation().Roll));
				}
				else
				{
					shakeRight = true;
				}
			}
			else
			{
				if (staticMesh->GetRelativeRotation().Pitch < baseRot->Pitch + shakingOffset)
				{
					staticMesh->SetRelativeRotation(FRotator(staticMesh->GetRelativeRotation().Pitch + (DeltaTime * speedShaking), staticMesh->GetRelativeRotation().Yaw, staticMesh->GetRelativeRotation().Roll));
				}
				else
				{
					shakeRight = false;
				}
			}
		}
	}

	if (platformFalling == true)
	{
		if (GetActorLocation().Z > basePos->Z - distance)
		{

			SetActorLocation(FVector(basePos->X, basePos->Y, GetActorLocation().Z - (DeltaTime * speed)));
		}

		if (GetActorLocation().Z <= basePos->Z - distance)
		{
			SetActorHiddenInGame(true);
			platformCollider->SetCollisionProfileName(TEXT("OverlapAll"));
			if (playFallSound == true)
			{
				StopFallSound_BP();
				playFallSound = false;
			}
			readyToRespawn = true;

		}
	}

	if (readyToRespawn)
	{
		timerBeforeRespawn -= DeltaTime;
		if (timerBeforeRespawn <= 0)
		{
			ResetValues();
		}
	}
}

