// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChargePlayer.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UChargePlayer : public UBTTaskNode
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector EntityActor;
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner_Comp, uint8* Node_Memory);
};
