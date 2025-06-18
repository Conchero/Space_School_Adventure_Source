// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthCollectible.h"
#include "Characters/MainCharacter.h"

void AHealthCollectible::CollectEffect(AMainCharacter* _character)
{
	Super::CollectEffect(_character);


	if (_character->m_health < _character->maxHealth)
	{
		_character->m_health += 1;
	}

}
