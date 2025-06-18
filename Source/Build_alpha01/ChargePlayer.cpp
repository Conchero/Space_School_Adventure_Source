// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargePlayer.h"

#include "EntityCharacter.h"
#include "EntityController_Common.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Characters/Ennemie.h"

EBTNodeResult::Type UChargePlayer::ExecuteTask(UBehaviorTreeComponent& Owner_Comp, uint8* Node_Memory)
{
	UBlackboardComponent* ownerBB = Owner_Comp.GetBlackboardComponent();
	ACharacter* entityToChase = Cast<ACharacter>(ownerBB->GetValueAsObject(EntityActor.SelectedKeyName));
	
	AEntityController_Common* const entityController = Cast<AEntityController_Common>(Owner_Comp.GetAIOwner());
	AEntityCharacter* const entityCharacter = Cast<AEntityCharacter>(entityController->GetPawn());
	AEnnemie* enemy = Cast<AEnnemie>(entityController->GetPawn());
	if (UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), entityCharacter->GetActorLocation(), entityToChase) != nullptr)
	{
		FVector launch = entityCharacter->GetActorForwardVector() * 500;
		launch.Z = 500;
	
		entityCharacter->LaunchCharacter(launch, false, true);
	}

	
	return EBTNodeResult::Type();
}
