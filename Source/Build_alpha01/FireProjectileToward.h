// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FireProjectileToward.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UFireProjectileToward : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector GoalPosition;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector InitPosition;
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
