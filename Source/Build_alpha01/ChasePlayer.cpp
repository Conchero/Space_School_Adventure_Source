// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"

#include "EntityCharacter.h"
#include "EntityController_Common.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& Owner_Comp, uint8* Node_Memory)
{
	UBlackboardComponent* ownerBB = Owner_Comp.GetBlackboardComponent();
	ACharacter* entityToChase = Cast<ACharacter>(ownerBB->GetValueAsObject(EntityActor.SelectedKeyName));
	
	AEntityController_Common* const entityController = Cast<AEntityController_Common>(Owner_Comp.GetAIOwner());
	AEntityCharacter* const entityCharacter = Cast<AEntityCharacter>(entityController->GetPawn());

	entityCharacter->UpdateWalkSpeed(ChaseSpeed);
	
	return EBTNodeResult::Type();
}
