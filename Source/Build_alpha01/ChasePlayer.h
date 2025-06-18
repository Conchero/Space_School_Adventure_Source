// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <msctf.h>

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector EntityActor;

	UPROPERTY(EditAnywhere)
	float ChaseSpeed;
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner_Comp, uint8* Node_Memory);

private:

	
};
