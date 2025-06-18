// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "RespawnableObjectArea.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API ARespawnableObjectArea : public ATriggerBox
{
	GENERATED_BODY()

public:
	ARespawnableObjectArea();
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	virtual void BeginPlay() override;
public:
	// In the constructor make sure to use AddDynamic to handle this function dynamically
	
	
};
