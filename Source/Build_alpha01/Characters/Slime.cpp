// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime.h"

ASlime::ASlime()
{
}

void ASlime::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetCharacterMovement()->IsMovingOnGround() == true)
	{
		if (playWalkingSound == false && GetCharacterMovement()->Velocity.Size() > 0.1f)
		{
			//PlayWalkingSound_BP();
			//playWalkingSound = true;
		}
		else if (playWalkingSound == true && GetCharacterMovement()->Velocity.Size() < 0.1f)
		{
			//StopWalkingSound_BP();
			//playWalkingSound = false;
		}
	}
}
