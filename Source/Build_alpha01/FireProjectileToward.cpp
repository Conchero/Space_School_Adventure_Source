// Fill out your copyright notice in the Description page of Project Settings.


#include "FireProjectileToward.h"

#include "Bullet.h"
#include "EntityCharacter.h"
#include "EntityController_Common.h"

EBTNodeResult::Type UFireProjectileToward::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* ownerBB = OwnerComp.GetBlackboardComponent();

	AEntityController_Common* entityController = Cast<AEntityController_Common>(OwnerComp.GetAIOwner());
	APawn* pawn = entityController->GetPawn();
	AEntityCharacter* entityCharacter = Cast<AEntityCharacter>(pawn);

	if (entityCharacter->bullet != nullptr)
	{
		/*	FRotator SpawnRotation = GetActorRotation();
				FVector SpawnPosition = spawner->GetComponentLocation()*/
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("shot")));
			GetWorld()->SpawnActor<AEntityBullet>(entityCharacter->bullet, (entityCharacter->GetActorLocation()+FVector::UpVector*20)+ entityCharacter->GetActorForwardVector()*100, entityCharacter->GetActorRotation());
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
