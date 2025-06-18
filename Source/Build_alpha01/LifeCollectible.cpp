// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeCollectible.h"
#include "Characters/MainCharacter.h"

void ALifeCollectible::CollectEffect(AMainCharacter* _character)
{
	Super::CollectEffect(_character);
	if (_character->life < 10)
	{
		_character->life++;
	}

}