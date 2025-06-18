// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomPatrol.h"

#include "EntityCharacter.h"
#include "EntityController_Common.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UFindRandomPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* ownerBB = OwnerComp.GetBlackboardComponent();

	AEntityController_Common* entityController = Cast<AEntityController_Common>(OwnerComp.GetAIOwner());
	APawn* pawn = entityController->GetPawn();
	ACharacter* entityCharacter = Cast<ACharacter>(pawn);
	if (entityCharacter != NULL)
	{
		if (UNavigationSystemV1::K2_GetRandomReachablePointInRadius(entityCharacter->GetWorld(), entityCharacter->GetActorLocation(), LocationToReach, PatrolRadius))
		{
			ownerBB->SetValueAsVector(location.SelectedKeyName, LocationToReach);
			entityController->MoveToLocation(LocationToReach);
		}
		else
		{
			ownerBB->SetValueAsVector(location.SelectedKeyName, entityCharacter->GetActorLocation());
		}
	}
	else
	{
		ownerBB->SetValueAsVector(location.SelectedKeyName, {0, 0, 0});
	}
	return EBTNodeResult::Type();
}
