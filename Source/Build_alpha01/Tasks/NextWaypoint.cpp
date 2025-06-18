// Fill out your copyright notice in the Description page of Project Settings.


#include "NextWaypoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Build_alpha01/WaypointTool.h"

EBTNodeResult::Type UNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* ownerBB = OwnerComp.GetBlackboardComponent();
	AWaypointTool* waypoint = Cast<AWaypointTool>(ownerBB->GetValueAsObject(Waypoint.SelectedKeyName));
	ownerBB->SetValueAsVector(PatrolLocation.SelectedKeyName, waypoint->GetActorLocation());
	ownerBB->SetValueAsObject(Waypoint.SelectedKeyName, waypoint->NextWaypoint);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
