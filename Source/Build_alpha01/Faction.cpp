// Fill out your copyright notice in the Description page of Project Settings.


#include "Faction.h"


// Sets default values for this component's properties
UFaction::UFaction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFaction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

#if WITH_EDITOR
void UFaction::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)  
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UFaction, CurrentFaction))
	{
		Allies.Empty();
		Neutral.Empty();
		Enemies.Empty();
		switch (CurrentFaction)
		{
		case FactionList::ROBOTS:
			Allies.Add(FactionList::PASSIVE_ANIMALS);
			Allies.Add(FactionList::NEUTRAL_ANIMALS);
			Allies.Add(FactionList::ROBOTS);
			Allies.Add(FactionList::PLAYER);
			Neutral.Add(FactionList::AGGRESSIVE_ANIMALS);
			Enemies.Add(FactionList::CORRUPTED_ROBOTS);
			break;
		case FactionList::CORRUPTED_ROBOTS:
			Allies.Add(FactionList::CORRUPTED_ROBOTS);
			Enemies.Add(FactionList::PLAYER);
			Enemies.Add(FactionList::PASSIVE_ANIMALS);
			Enemies.Add(FactionList::NEUTRAL_ANIMALS);
			Enemies.Add(FactionList::AGGRESSIVE_ANIMALS);
			Enemies.Add(FactionList::ROBOTS);
			break;
		case FactionList::PASSIVE_ANIMALS:
			Allies.Add(FactionList::ROBOTS);
			Allies.Add(FactionList::PASSIVE_ANIMALS);
			Allies.Add(FactionList::NEUTRAL_ANIMALS);
			Neutral.Add(FactionList::NEUTRAL_ANIMALS);
			Afraid.Add(FactionList::AGGRESSIVE_ANIMALS);
			Afraid.Add(FactionList::CORRUPTED_ROBOTS);
			break;
		case FactionList::NEUTRAL_ANIMALS:
			Allies.Add(FactionList::PASSIVE_ANIMALS);
			Allies.Add(FactionList::NEUTRAL_ANIMALS);
			Neutral.Add(FactionList::PLAYER);
			Neutral.Add(FactionList::ROBOTS);
			Neutral.Add(FactionList::AGGRESSIVE_ANIMALS);
			Neutral.Add(FactionList::CORRUPTED_ROBOTS);
			break;
		case FactionList::AGGRESSIVE_ANIMALS:
			Enemies.Add(FactionList::PLAYER);
			Enemies.Add(FactionList::AGGRESSIVE_ANIMALS);
			Enemies.Add(FactionList::PASSIVE_ANIMALS);
			Enemies.Add(FactionList::NEUTRAL_ANIMALS);
			Enemies.Add(FactionList::ROBOTS);
			Enemies.Add(FactionList::CORRUPTED_ROBOTS);
			break;
		}
		
	}
	
}
#endif WITH_EDITOR


// Called every frame
void UFaction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


