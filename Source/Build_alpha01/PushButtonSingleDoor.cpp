// Fill out your copyright notice in the Description page of Project Settings.


#include "PushButtonSingleDoor.h"
#include "SingleDoor.h"

void APushButtonSingleDoor::BeginPlay()
{
	Super::BeginPlay();

	
}

void APushButtonSingleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		for (int i = 0; i < doorToOpen.Num(); i++)
		{
			if (doorToOpen[i] != nullptr)
			{
				doorToOpen[i]->activateBehaviour = activateBehaviour;
			}
		}
	
	

}



