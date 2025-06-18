// Fill out your copyright notice in the Description page of Project Settings.


#include "Explode.h"

#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Build_alpha01/EntityCharacter.h"
#include "Build_alpha01/Characters/Ennemie.h"
#include "Build_alpha01/Characters/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UExplode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* ownerBB = OwnerComp.GetBlackboardComponent();
	AController* ownerActorController = Cast<AController>(ownerBB->GetOwner());
	AActor* ownerActor = ownerActorController->GetPawn();

	AEnnemie* enemy = Cast<AEnnemie>(ownerActorController->GetPawn());
	 
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(),  actors);
	for ( AActor* actorBis: actors)
	{
		if (FVector::Dist(ownerActor->GetActorLocation(), actorBis->GetActorLocation()) < ExplosionDistance)
		{
			AMainCharacter* entityMainCharacter = Cast<AMainCharacter>(actorBis);
			AEnnemie* entityOtherCharacter = Cast<AEnnemie>(actorBis);
			if (entityMainCharacter)
			{
				enemy->PlayRobotExplodeSound_BP();
				entityMainCharacter->RemoveLife(1.0f, true, EAxis::Y);
			}
			if (entityOtherCharacter)
			{
				entityOtherCharacter->RemoveLife(1.0f, ownerActor);
			}
		}
	}
	ownerActor->SetLifeSpan(0.1f);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
