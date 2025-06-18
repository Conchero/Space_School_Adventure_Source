// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeBonusCollectible.h"
#include "Characters/MainCharacter.h"

void ALifeBonusCollectible::CollectEffect(class AMainCharacter* _character)
{
Super::CollectEffect(_character);
	if (_character != nullptr)
	{
		_character->maxHealth = 6;
		_character->m_health = _character->maxHealth;
	}
}
