// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectibles.h"
#include "LifeBonusCollectible.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API ALifeBonusCollectible : public ACollectibles
{
	GENERATED_BODY()

  void CollectEffect(class AMainCharacter* _character) override;
	
};
