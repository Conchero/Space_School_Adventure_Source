// Fill out your copyright notice in the Description page of Project Settings.


#include "RayProjectile.h"

#include <string>

#include "DrawDebugHelpers.h"
#include "Build_alpha01/Characters/Ennemie.h"
#include "Build_alpha01/Characters/MainCharacter.h"

// Sets default values
ARayProjectile::ARayProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARayProjectile::BeginPlay()
{
	
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Init");
	SetLifeSpan(1.0f);
}

// Called every frame
void ARayProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugLine(GetWorld(), InitPos, GoalPos, FColor::Red);
}

void ARayProjectile::LifeSpanExpired()
{
	Super::LifeSpanExpired();
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, Caster);
	FHitResult hit;
	if (GetWorld()->LineTraceSingleByChannel(OUT hit,
		InitPos,
		GoalPos,
		ECC_Pawn,
		TraceParams
		))
	{
		if (hit.Actor->GetName() != Caster->GetName())
		{
			
			AMainCharacter* entityMainCharacter = Cast<AMainCharacter>(hit.Actor);
			AEnnemie* entityOtherCharacter = Cast<AEnnemie>(hit.Actor);
			if (entityMainCharacter)
			{
				if (castingEnemy != nullptr)
				{
					castingEnemy->PlayRobotAttackSound_BP();
				}
				entityMainCharacter->RemoveLife(1.0f, true, EAxis::Y);
			}
			if (entityOtherCharacter)
			{
				entityOtherCharacter->RemoveLife(1.0f, Caster);
			}
		}
	}

}

