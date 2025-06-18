// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleDoor.h"

// Sets default values
ASingleDoor::ASingleDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	audioComponent = CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASingleDoor::BeginPlay()
{
	Super::BeginPlay();
	doorBaseRot = new FRotator(GetActorRotation());
	doorBasePos = new FVector(GetActorLocation());
}

// Called every frame
void ASingleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OpenDoor(DeltaTime);
}


void ASingleDoor::OpenDoor(float DeltaTime)
{
	switch (doorMovement)
	{
	case DoorMovement::ROTATE_CLOCKWISE:
		if (activateBehaviour)
		{
			if (GetActorRotation().Yaw < doorBaseRot->Yaw + rotationOfDoor)
			{
				SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + (DeltaTime * speedOpeningDoor), GetActorRotation().Roll));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (GetActorRotation().Yaw > doorBaseRot->Yaw)
			{
				SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - (DeltaTime * speedClosingDoor), GetActorRotation().Roll));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;
	case DoorMovement::ROTATE_COUNTERCLOCK:
		if (activateBehaviour)
		{
			if (GetActorRotation().Yaw > doorBaseRot->Yaw - rotationOfDoor)
			{
				SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - (DeltaTime * speedOpeningDoor), GetActorRotation().Roll));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (GetActorRotation().Yaw < doorBaseRot->Yaw)
			{
				SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + (DeltaTime * speedClosingDoor), GetActorRotation().Roll));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;

	case DoorMovement::TRANSLATE_HL:
		if (activateBehaviour)
		{
			if (GetActorLocation().X > doorBasePos->X - translateOfDoor)
			{
				SetActorLocation(FVector(GetActorLocation().X - (DeltaTime * speedOpeningDoor), GetActorLocation().Y, GetActorLocation().Z));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (GetActorLocation().X < doorBasePos->X)
			{
				SetActorLocation(FVector(GetActorLocation().X + (DeltaTime * speedClosingDoor), GetActorLocation().Y, GetActorLocation().Z));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;

	case DoorMovement::TRANSLATE_HR:
		if (activateBehaviour)
		{
			if (GetActorLocation().X < doorBasePos->X + translateOfDoor)
			{
				SetActorLocation(FVector(GetActorLocation().X + (DeltaTime * speedOpeningDoor), GetActorLocation().Y, GetActorLocation().Z));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (GetActorLocation().X > doorBasePos->X)
			{
				SetActorLocation(FVector(GetActorLocation().X - (DeltaTime * speedClosingDoor), GetActorLocation().Y, GetActorLocation().Z));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;
	case DoorMovement::TRANSLATE_HF:
		if (activateBehaviour)
		{
			if (GetActorLocation().Y > doorBasePos->Y - translateOfDoor)
			{
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y - (DeltaTime * speedOpeningDoor), GetActorLocation().Z));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (GetActorLocation().Y < doorBasePos->Y)
			{
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y + (DeltaTime * speedClosingDoor), GetActorLocation().Z));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;

	case DoorMovement::TRANSLATE_HB:
		if (activateBehaviour)
		{
			if (GetActorLocation().Y < doorBasePos->Y + translateOfDoor)
			{
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y + (DeltaTime * speedOpeningDoor), GetActorLocation().Z));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (GetActorLocation().Y > doorBasePos->Y)
			{
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y - (DeltaTime * speedClosingDoor), GetActorLocation().Z));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;
	case DoorMovement::TRANSLATE_F:

		if (activateBehaviour)
		{
			if (FVector::Dist(GetActorLocation(), *doorBasePos) < translateOfDoor)
			{
				SetActorLocation(GetActorLocation() + GetActorForwardVector() * DeltaTime * speedOpeningDoor);
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (FVector::Dist(GetActorLocation(), *doorBasePos) > translateOfDoor)
			{
				SetActorLocation(GetActorLocation() - GetActorForwardVector() * DeltaTime * speedClosingDoor);
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;

	case DoorMovement::TRANSLATE_R:

		if (activateBehaviour)
		{
			if (FVector::Dist(GetActorLocation(), *doorBasePos) < translateOfDoor)
			{
				SetActorLocation(GetActorLocation() + GetActorRightVector() * DeltaTime * speedOpeningDoor);
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (FVector::Dist(GetActorLocation(), *doorBasePos) > 10)
			{
				SetActorLocation(GetActorLocation() - GetActorRightVector() * DeltaTime * speedClosingDoor);
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;

	case DoorMovement::TRANSLATE_VU:
		if (activateBehaviour)
		{

			if (GetActorLocation().Z < doorBasePos->Z + translateOfDoor)
			{
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + (DeltaTime * speedOpeningDoor)));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (GetActorLocation().Z > doorBasePos->Z)
			{
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - (DeltaTime * speedClosingDoor)));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;

	case DoorMovement::TRANSLATE_VD:
		if (activateBehaviour)
		{
			if (GetActorLocation().Z > doorBasePos->Z - translateOfDoor)
			{
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - (DeltaTime * speedOpeningDoor)));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		else if (activateBehaviour == false)
		{
			if (GetActorLocation().Z < doorBasePos->Z)
			{
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + (DeltaTime * speedClosingDoor)));
				if (OpeningSoundPlaying == false)
				{
					PlayOpeningSound_BP();
					OpeningSoundPlaying = true;
				}
			}
			else
			{
				if (OpeningSoundPlaying == true)
				{
					StopOpeningSound_BP();
					OpeningSoundPlaying = false;

				}
			}
		}
		break;
	default:
		break;
	}
}
