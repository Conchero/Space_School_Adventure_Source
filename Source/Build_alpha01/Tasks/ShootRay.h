// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ShootRay.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UShootRay : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Parameters")
	float RayDuration;
	UPROPERTY(EditAnywhere, Category="Parameters")
	float RayDamage;;
	
	UPROPERTY(EditAnywhere, Category="Parameters")
	FBlackboardKeySelector InitObject;
	
	UPROPERTY(EditAnywhere, Category="Parameters")
	FBlackboardKeySelector GoalObject;
	
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
