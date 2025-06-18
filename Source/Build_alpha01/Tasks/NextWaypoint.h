// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Variables")
	FBlackboardKeySelector Waypoint;
	
	UPROPERTY(EditAnywhere, Category = "Variables")
	FBlackboardKeySelector PatrolLocation;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
