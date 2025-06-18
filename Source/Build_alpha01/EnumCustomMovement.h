// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EMovementModeCustom
{
	CUSTOM_NONE UMETA(DisplayName = "None"),
	CUSTOM_GRIP_PLATFORM UMETA(DisplayName = "Climbing"),
	CUSTOM_MAX UMETA(Hidden),

};
