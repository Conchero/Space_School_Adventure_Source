// Fill out your copyright notice in the Description page of Project Settings.


#include "FindNextWaypoint.h"

#include "EntityController_Common.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UFindNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* ownerBB = OwnerComp.GetBlackboardComponent();
	
	if (Cast<AWaypointTool>(ownerBB->GetValueAsObject(Waypoint.SelectedKeyName))->NextWaypoint != nullptr)
	{
		
		ownerBB->SetValueAsObject(Waypoint.SelectedKeyName, Cast<AWaypointTool>(ownerBB->GetValueAsObject(Waypoint.SelectedKeyName))->NextWaypoint);
	}
	else
	{
		ownerBB->ClearValue(Waypoint.SelectedKeyName);
	}
	
	return EBTNodeResult::Type();
}
