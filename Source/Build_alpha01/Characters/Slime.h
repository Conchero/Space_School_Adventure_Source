// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ennemie.h"
#include "Slime.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API ASlime : public AEnnemie
{
	GENERATED_BODY()
public:

	ASlime();

	virtual void Tick(float DeltaSeconds) override;
protected:
	bool playWalkingSound = false;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayWalkingSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void StopWalkingSound_BP();
};
