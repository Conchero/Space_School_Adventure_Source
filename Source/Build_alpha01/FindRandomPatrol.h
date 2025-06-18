// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindRandomPatrol.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UFindRandomPatrol : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	class UNavigationSystemV1* NavSys;

public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector location;

	UPROPERTY()
	FVector LocationToReach;

	UPROPERTY(EditAnywhere)
	float PatrolSpeed = 125.0f;

	UPROPERTY(EditAnywhere)
	float PatrolRadius = 125.0f;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
