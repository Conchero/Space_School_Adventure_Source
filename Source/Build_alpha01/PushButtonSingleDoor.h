// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PushButton.h"
#include "PushButtonSingleDoor.generated.h"

/**
 *
 */





UCLASS()
class BUILD_ALPHA01_API APushButtonSingleDoor : public APushButton
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;


	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		TArray<class ASingleDoor*> doorToOpen;


};
