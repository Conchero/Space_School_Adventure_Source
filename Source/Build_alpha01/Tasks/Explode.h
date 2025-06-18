// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Explode.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UExplode : public UBTTaskNode
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category="Parameters")
	float ExplosionDistance;
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
