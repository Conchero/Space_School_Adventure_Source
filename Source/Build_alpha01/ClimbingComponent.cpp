// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbingComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Components/InputComponent.h"
#include "EnumCustomMovement.h"
#include "Characters/MainCharacter.h"

void UClimbingComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);

	switch ((EMovementModeCustom)CustomMovementMode)
	{
	case EMovementModeCustom::CUSTOM_NONE :
		break;
	case EMovementModeCustom::CUSTOM_GRIP_PLATFORM:
		PhysGripPlatform(deltaTime, Iterations);
		break;
	default:
		break;
	}
}

void UClimbingComponent::PhysGripPlatform(float deltaTime, int32 Iterations)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player life after")));
}

void UClimbingComponent::GripPlatform()
{
	if (CustomMovementMode == EMovementModeCustom::CUSTOM_NONE)
	{
		SetMovementMode(MOVE_None, EMovementModeCustom::CUSTOM_GRIP_PLATFORM);
		CustomMovementMode = EMovementModeCustom::CUSTOM_GRIP_PLATFORM;

		
	}
}

void UClimbingComponent::UngripPlatform()
{

	if (CustomMovementMode == EMovementModeCustom::CUSTOM_GRIP_PLATFORM)
	{
		SetMovementMode(MOVE_Falling, EMovementModeCustom::CUSTOM_NONE);
		CustomMovementMode = EMovementModeCustom::CUSTOM_NONE;
	}
}

void UClimbingComponent::AttachPlayerToPlatform(AActor* _other)
{

	AMainCharacter* player = Cast<AMainCharacter>(GetOwner());

	if (player != nullptr)
	{
		player->AttachToActor(_other,FAttachmentTransformRules::KeepWorldTransform);
	}

}

void UClimbingComponent::DetachPlayerFromPlatform()
{
	AMainCharacter* player = Cast<AMainCharacter>(GetOwner());

	if (player != nullptr)
	{
		player->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
}

