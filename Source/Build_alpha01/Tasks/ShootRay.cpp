// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootRay.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Build_alpha01/Characters/Ennemie.h"
#include "Build_alpha01/Characters/MainCharacter.h"
#include "Build_alpha01/EntityWeapons/RayProjectile.h"
#include "../Characters/Ennemie.h"

EBTNodeResult::Type UShootRay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* ownerBB = OwnerComp.GetBlackboardComponent();
	AController* ownerActorController = Cast<AController>(ownerBB->GetOwner());
	AActor* ownerActor = ownerActorController->GetPawn();
	AEnnemie* enemy = Cast<AEnnemie>(ownerActorController->GetPawn());

	ARayProjectile* ray = GetWorld()->SpawnActor<ARayProjectile>(ownerActor->GetActorLocation(), ownerActor->GetActorRotation());

	ray->InitPos = Cast<AActor>(ownerBB->GetValueAsObject(InitObject.SelectedKeyName))->GetActorLocation();
	ray->GoalPos = Cast<AActor>(ownerBB->GetValueAsObject(GoalObject.SelectedKeyName))->GetActorLocation();
	ray->SetLifeSpan(RayDuration);
	
	ray->RayDamage = RayDamage;
	ray->Caster = ownerActor;
	ray->castingEnemy = enemy;
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
