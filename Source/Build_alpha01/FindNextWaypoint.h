// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UObject/Object.h"
#include "FindNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UFindNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Waypoint;
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
