// Fill out your copyright notice in the Description page of Project Settings.


#include "SniperBullet.h"
#include "Characters/MainCharacter.h"

ASniperBullet::ASniperBullet()
{

	speed = 500;
}

void ASniperBullet::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		Cast<AMainCharacter>(OtherActor)->RemoveLife(damage, true, launchCharacterDir);
		Cast<AMainCharacter>(OtherActor)->PlayImpactSound_BP();
		Destroy();
	}

}

void ASniperBullet::OnJumpCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("jump")));
		Cast<AMainCharacter>(OtherActor)->GetCharacterMovement()->Launch(GetActorUpVector() * 1000);
		Destroy();
	}
}