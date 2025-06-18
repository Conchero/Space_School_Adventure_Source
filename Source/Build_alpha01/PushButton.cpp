// Fill out your copyright notice in the Description page of Project Settings.


#include "PushButton.h"
#include "Components/BoxComponent.h"
#include "Math/Vector.h"
#include "Characters/Ennemie.h"
#include "LouisCharacter.h"


// Sets default values
APushButton::APushButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	buttonPressed = false;
	activateBehaviour = false;
	speed = 40;
}

void APushButton::PushButtonBehaviourEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEnnemie>(OtherActor) == nullptr && Cast<ALouisCharacter>(OtherActor) == nullptr)
	{
		if (triggeredActor == nullptr)
		{
			triggeredActor = OtherActor;
			buttonPressed = true;
		}
	}
}

void APushButton::PushButtonBehaviourExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (triggeredActor != nullptr)
	{
		if (triggeredActor == OtherActor)
		{
			buttonPressed = false;
			activateBehaviour = false;
			triggeredActor = nullptr;
		}

	}

}

// Called when the game starts or when spawned
void APushButton::BeginPlay()
{
	Super::BeginPlay();

	collider = this->FindComponentByClass<UBoxComponent>();
	basePos = new FVector(GetActorLocation());
	if (collider != nullptr)
	{
		collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APushButton::PushButtonBehaviourEnter);

		if (buttonType == ButtonType::COUNT_DOWN)
		{
			collider->OnComponentEndOverlap.AddUniqueDynamic(this, &APushButton::PushButtonBehaviourExit);
		}
	}
}

// Called every frame
void APushButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (buttonPressed == true)
	{
		if (GetActorLocation().Z > basePos->Z - 20)
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - (DeltaTime * speed)));
		}
		else if (GetActorLocation().Z <= basePos->Z - 20)
		{
			activateBehaviour = true;
		}
	}
	else if (buttonPressed == false)
	{
		if (GetActorLocation().Z < basePos->Z)
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + (DeltaTime * speed)));
		}
	}

}

