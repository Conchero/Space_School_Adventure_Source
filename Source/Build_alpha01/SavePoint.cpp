// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePoint.h"
#include "Characters/MainCharacter.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>
#include <GameFramework/Controller.h>

// Sets default values
ASavePoint::ASavePoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("SavePointMesh");
}

// Called when the game starts or when spawned
void ASavePoint::BeginPlay()
{
	Super::BeginPlay();
	lilly = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ASavePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	distPointCharacter.X = FMath::Abs(lilly->GetActorLocation().X - GetActorLocation().X);
	distPointCharacter.Y = FMath::Abs(lilly->GetActorLocation().Y - GetActorLocation().Y);
	distPointCharacter.Z = 0;
	if (distPointCharacter.X < 140 && distPointCharacter.Y < 140)
	{
		lilly->canSaveGame = true;
		lilly->ShowSaveFX = true;
	}
	else
	{
		lilly->canSaveGame = false;
		lilly->ShowSaveFX = false;
	}
}



