// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Climbable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClimbable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUILD_ALPHA01_API IClimbable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void StayGripped();
};
