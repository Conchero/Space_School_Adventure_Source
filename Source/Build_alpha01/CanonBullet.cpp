// Fill out your copyright notice in the Description page of Project Settings.


#include "CanonBullet.h"
#include "Characters/MainCharacter.h"
#include "LouisCharacter.h"

ACanonBullet::ACanonBullet()
{
	
	speed = 500;
}

void ACanonBullet::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		Cast<AMainCharacter>(OtherActor)->RemoveLife(damage, true, launchCharacterDir);
		Cast<AMainCharacter>(OtherActor)->PlayImpactSound_BP();
		PlayExplodeSound_BP();
	}
	if (Cast<ABullet>(OtherActor) == nullptr && Cast<ALouisCharacter>(OtherActor) == nullptr)
	{
		PlayExplodeSound_BP();
		Destroy();
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player")));
	}
}

void ACanonBullet::OnJumpCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		Cast<AMainCharacter>(OtherActor)->GetCharacterMovement()->Launch(GetActorUpVector() * 1000);
		PlayExplodeSound_BP();
		Destroy();
	}
}
