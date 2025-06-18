// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CommandTriggerVolume.generated.h"

/**
 * 
 */
class UTexture2D;
class FText;

UCLASS()
class BUILD_ALPHA01_API ACommandTriggerVolume : public ATriggerBox
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText command;
};
