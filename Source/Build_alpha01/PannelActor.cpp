// Fill out your copyright notice in the Description page of Project Settings.


#include "PannelActor.h"
#include "Components/BoxComponent.h"
#include "Characters/MainCharacter.h"

APannelActor::APannelActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	boxCollider = CreateDefaultSubobject<UBoxComponent>(FName("box collider"));
	boxCollider->SetupAttachment(RootComponent);
}

void APannelActor::BeginPlay()
{
	Super::BeginPlay();
	boxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APannelActor::OnEnter);
	boxCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &APannelActor::OnExit);
}

void APannelActor::OnEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		ShowText_BP();
	}
}

void APannelActor::OnExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		HideText_BP();
	}
}
