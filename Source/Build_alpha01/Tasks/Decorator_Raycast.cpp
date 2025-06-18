// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator_Raycast.h"

#include "Build_alpha01/EntityCharacter.h"

bool UDecorator_Raycast::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* ownerBB = OwnerComp.GetBlackboardComponent();
	AActor* ownerActor = ownerBB->GetOwner();
	if (ownerBB)
	{
		FVector startPos = Cast<AActor>(ownerBB->GetValueAsObject(StartPosition.SelectedKeyName))->GetActorLocation();
		FVector goalPos= Cast<AActor>(ownerBB->GetValueAsObject(GoalPosition.SelectedKeyName))->GetActorLocation();
		
	

		FHitResult hit;
		if (GetWorld()->LineTraceSingleByChannel(OUT hit,
			startPos,
			goalPos,
			ECollisionChannel::ECC_Visibility
			))
		{
			return false;
		}
	
		return true;
	}
	return false;
}
