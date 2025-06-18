// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_Raycast.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UDecorator_Raycast : public UBTDecorator
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category=Condition)
	FBlackboardKeySelector StartPosition;
	
	UPROPERTY(EditAnywhere, Category=Condition)
	FBlackboardKeySelector GoalPosition;
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

