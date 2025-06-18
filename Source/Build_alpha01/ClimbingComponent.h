// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NinjaCharacterMovementComponent.h"
#include "ClimbingComponent.generated.h"

/**
 *
 */
UCLASS()
class BUILD_ALPHA01_API UClimbingComponent : public UNinjaCharacterMovementComponent
{
	GENERATED_BODY()

public:

	virtual void PhysCustom(float deltaTime, int32 Iterations)override;
    virtual void PhysGripPlatform(float deltaTime, int32 Iterations);


	void GripPlatform();
	void UngripPlatform();

	void AttachPlayerToPlatform(class AActor* _other);
	void DetachPlayerFromPlatform();
};
