// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectibles.h"
#include "HealthCollectible.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API AHealthCollectible : public ACollectibles
{
	GENERATED_BODY()
public:
virtual void CollectEffect(class AMainCharacter* _character) override;

};
