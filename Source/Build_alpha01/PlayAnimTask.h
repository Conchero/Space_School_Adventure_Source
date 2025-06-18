// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PlayAnimTask.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API UPlayAnimTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UAnimSequence* blueprintToPlay;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
