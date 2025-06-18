// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesCountTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Characters/Ennemie.h"
#include "SingleDoor.h"
#include "Characters/MainCharacter.h"

// Sets default values
AEnemiesCountTriggerBox::AEnemiesCountTriggerBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	activateBehaviour = false;

}

// Called when the game starts or when spawned
void AEnemiesCountTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	triggerBox = FindComponentByClass<UBoxComponent>();
}

// Called every frame
void AEnemiesCountTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	triggerBox->GetOverlappingActors(OUT enemies, AEnnemie::StaticClass());
	triggerBox->GetOverlappingActors(OUT player, AMainCharacter::StaticClass());

	if (player.Num() != 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%d"), enemies.Num()));
		if (player[0] != nullptr)
		{
			playerIn = Cast<AMainCharacter>(player[0]);
			playerIn->countTriggerIn = this;
		}
		//showWidgetEnemyCount = true;
	}
	else
	{
		if (playerIn != nullptr)
		{
			playerIn->countTriggerIn = nullptr;
			playerIn = nullptr;
		}
	}
	if (enemies.Num() <= 0)
	{
		activateBehaviour = true;
	}
	else
	{
		activateBehaviour = false;

	}

	for (int i = 0; i < doorToOpen.Num(); i++)
	{
		if (doorToOpen[i] != nullptr)
		{
			doorToOpen[i]->activateBehaviour = activateBehaviour;
		}
	}
}

