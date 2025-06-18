// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeKeyBoardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChangeKeyBoardValue::ExecuteTask(UBehaviorTreeComponent& Owner_Comp, uint8* Node_Memory)
{
	UBlackboardComponent* ownerBB = Owner_Comp.GetBlackboardComponent();

	ownerBB->SetValueAsBool(KeyToChange.SelectedKeyName, false);
	ownerBB->ClearValue(KeyToChangeTwo.SelectedKeyName);
	
	return EBTNodeResult::Type();
}
