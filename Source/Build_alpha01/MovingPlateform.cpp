// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlateform.h"
#include "Math/Vector.h"



// Sets default values
AMovingPlateform::AMovingPlateform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	speed = 100;
	distance = 100;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	audioComponent = CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMovingPlateform::BeginPlay()
{
	Super::BeginPlay();

	basePos = new FVector(GetActorLocation());

	PlayHooverSound_BP();


	switch (moveDir)
	{
	case MovementPlatform::TRANSLATE_LEFT_FIRST:
		goRight = false;
		goLeft = true;
		goForward = false;
		goBack = false;
		goUp = false;
		goDown = false;
		break;
	case MovementPlatform::TRANSLATE_RIGHT_FIRST:
		goRight = true;
		goLeft = false;
		goForward = false;
		goBack = false;
		goUp = false;
		goDown = false;
		break;
	case MovementPlatform::TRANSLATE_UP_FIRST:
		goRight = false;
		goLeft = false;
		goForward = false;
		goBack = false;
		goUp = true;
		goDown = false;
		break;
	case MovementPlatform::TRANSLATE_DOWN_FIRST:
		goRight = false;
		goLeft = false;
		goForward = false;
		goBack = false;
		goUp = false;
		goDown = true;
		break;
	case MovementPlatform::TRANSLATE_FORWARD_FIRST:
		goRight = false;
		goLeft = false;
		goForward = true;
		goBack = false;
		goUp = false;
		goDown = false;
		break;
	case MovementPlatform::TRANSLATE_BACK_FIRST:
		goRight = false;
		goLeft = false;
		goForward = false;
		goBack = true;
		goUp = false;
		goDown = false;
		break;
	default:
		break;
	}





}

// Called every frame
void AMovingPlateform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (moveDir)
	{
	case MovementPlatform::TRANSLATE_LEFT_FIRST:
		if (goRight == true)
		{
			if (GetActorLocation().Y < basePos->Y + distance)
			{
				SetActorLocation(FVector(basePos->X, GetActorLocation().Y + (DeltaTime * speed), basePos->Z));
			}

			if (GetActorLocation().Y >= basePos->Y + 100)
			{
				goLeft = true;
				goRight = false;
			}

		}

		if (goLeft == true)
		{
			if (GetActorLocation().Y > basePos->Y - distance)
			{
				SetActorLocation(FVector(basePos->X, GetActorLocation().Y - (DeltaTime * speed), basePos->Z));
			}

			if (GetActorLocation().Y <= basePos->Y - distance)
			{
				goRight = true;
				goLeft = false;
			}
		}
		break;
	case MovementPlatform::TRANSLATE_RIGHT_FIRST:
		if (goRight == true)
		{
			if (GetActorLocation().Y < basePos->Y + distance)
			{
				SetActorLocation(FVector(basePos->X, GetActorLocation().Y + (DeltaTime * speed), basePos->Z));
			}

			if (GetActorLocation().Y >= basePos->Y + distance)
			{
				goLeft = true;
				goRight = false;
			}

		}

		if (goLeft == true)
		{
			if (GetActorLocation().Y > basePos->Y - distance)
			{
				SetActorLocation(FVector(basePos->X, GetActorLocation().Y - (DeltaTime * speed), basePos->Z));
			}

			if (GetActorLocation().Y <= basePos->Y - distance)
			{
				goRight = true;
				goLeft = false;
			}
		}
		break;
	case MovementPlatform::TRANSLATE_UP_FIRST:
		if (goUp == true)
		{
			if (GetActorLocation().Z < basePos->Z + distance)
			{
				SetActorLocation(FVector(basePos->X, basePos->Y, GetActorLocation().Z + (DeltaTime * speed)));
			}

			if (GetActorLocation().Z >= basePos->Z + distance)
			{
				goUp = false;
				goDown = true;
			}

		}

		if (goDown == true)
		{
			if (GetActorLocation().Z > basePos->Z - distance)
			{
				SetActorLocation(FVector(basePos->X, basePos->Y, GetActorLocation().Z - (DeltaTime * speed)));
			}

			if (GetActorLocation().Z <= basePos->Z - distance)
			{
				goUp = true;
				goDown = false;
			}
		}
		break;
	case MovementPlatform::TRANSLATE_DOWN_FIRST:
		if (goUp == true)
		{
			if (GetActorLocation().Z < basePos->Z + distance)
			{
				SetActorLocation(FVector(basePos->X, basePos->Y, GetActorLocation().Z + (DeltaTime * speed)));
			}

			if (GetActorLocation().Z >= basePos->Z + distance)
			{
				goUp = false;
				goDown = true;
			}

		}

		if (goDown == true)
		{
			if (GetActorLocation().Z > basePos->Z - distance)
			{
				SetActorLocation(FVector(basePos->X, basePos->Y, GetActorLocation().Z - (DeltaTime * speed)));
			}

			if (GetActorLocation().Z <= basePos->Z - distance)
			{
				goUp = true;
				goDown = false;
			}
		}
		break;
	case MovementPlatform::TRANSLATE_FORWARD_FIRST:

		if (goForward == true)
		{
			if (GetActorLocation().X < basePos->X + distance)
			{
				SetActorLocation(FVector(GetActorLocation().X + (DeltaTime * speed), basePos->Y, basePos->Z));
			}

			if (GetActorLocation().X >= basePos->X + distance)
			{
				goForward = false;
				goBack = true;
			}

		}
		if (goBack == true)
		{
			if (GetActorLocation().X > basePos->X - distance)
			{
				SetActorLocation(FVector(GetActorLocation().X - (DeltaTime * speed), basePos->Y, basePos->Z));
			}

			if (GetActorLocation().X <= basePos->X - distance)
			{
				goForward = true;
				goBack = false;
			}
		}

		break;
	case MovementPlatform::TRANSLATE_BACK_FIRST:

		if (goForward == true)
		{
			if (GetActorLocation().X < basePos->X + distance)
			{
				SetActorLocation(FVector(GetActorLocation().X + (DeltaTime * speed), basePos->Y, basePos->Z));
			}

			if (GetActorLocation().X >= basePos->X + distance)
			{
				goForward = false;
				goBack = true;
			}

		}
		if (goBack == true)
		{
			if (GetActorLocation().X > basePos->X - distance)
			{
				SetActorLocation(FVector(GetActorLocation().X - (DeltaTime * speed), basePos->Y, basePos->Z));
			}

			if (GetActorLocation().X <= basePos->X - distance)
			{
				goForward = true;
				goBack = false;
			}
		}

		break;
	default:
		break;
	}

}

