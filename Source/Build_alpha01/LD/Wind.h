// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "Wind.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API AWind : public AVolume
{
	GENERATED_BODY()
public:
	AWind();

	UPROPERTY(EditAnywhere)
	FVector WindForce;
	
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaSeconds) override;
	// In the constructor make sure to use AddDynamic to handle this function dynamically
	
	
};
