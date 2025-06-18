// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityController_Common.h"

#include <Audioclient.h>

#include "EntityCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Characters/Ennemie.h"

AEntityController_Common::AEntityController_Common()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	EntitySightComponent = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight"));
	EntityHearComponent = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AI Hear"));
	EntityDamagedComponent = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("AI Damaging"));

	EntitySightComponent->DetectionByAffiliation.bDetectNeutrals = true;
	EntitySightComponent->DetectionByAffiliation.bDetectFriendlies = true;
	EntitySightComponent->DetectionByAffiliation.bDetectEnemies = true;
	EntityHearComponent->DetectionByAffiliation.bDetectNeutrals = true;
	EntityHearComponent->DetectionByAffiliation.bDetectFriendlies = true;
	EntityHearComponent->DetectionByAffiliation.bDetectEnemies = true;
	
	PerceptionComponent->ConfigureSense(*EntitySightComponent);
	PerceptionComponent->ConfigureSense(*EntityHearComponent);
	PerceptionComponent->ConfigureSense(*EntityDamagedComponent);
}

void AEntityController_Common::BeginPlay()
{
	Super::BeginPlay();
	GetAIPerceptionComponent()->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AEntityController_Common::OnPerceptionUpdate);
}


void AEntityController_Common::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (GetBlackboardComponent() != nullptr && Cast<AEnnemie>(GetPawn()) != nullptr)
	{
		GetBlackboardComponent()->SetValueAsBool("isFreezed", Cast<AEnnemie>(GetPawn())->IsFreezed);
		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("%d"), GetBlackboardComponent()->GetValueAsBool("isFreezed")));
	}

}

void AEntityController_Common::OnPerceptionUpdate(AActor* actor, FAIStimulus stimulus)
{
	
	UFaction* faction = actor->FindComponentByClass<UFaction>();
	
	if (Cast<AEntityCharacter>(GetPawn())->Senses.Contains(stimulus.Type.Name))
	{
		if (stimulus.Type.Name == "Default__AISense_Damage")
		{
			TArray<AActor*> actors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntityCharacter::StaticClass(),  actors);
			for ( AActor* actorBis: actors)
			{
				AEntityCharacter* entity = Cast<AEntityCharacter>(actorBis);
				if (FVector::Dist(GetPawn()->GetActorLocation(), actorBis->GetActorLocation()) < Cast<AEntityCharacter>(GetPawn())->NeutralDistanceCall)
				{
					AEntityController_Common* controller = Cast<AEntityController_Common>(entity->Controller);
					controller->GetBlackboardComponent()->SetValueAsBool(HasLineOfSight, true);
					controller->GetBlackboardComponent()->SetValueAsBool(IsChasingEnemy, true);
					controller->GetBlackboardComponent()->SetValueAsObject(EntityToChase, actor);
					entity->Faction->Enemies.Add(actor->FindComponentByClass<UFaction>()->CurrentFaction);
				}
			}
		}
		if (faction && !actor->IsUnreachable())
		{
			if (GetPawn()->FindComponentByClass<UFaction>()->Enemies.Contains(faction->CurrentFaction) && stimulus.WasSuccessfullySensed())
			{
				GetBlackboardComponent()->SetValueAsBool(HasLineOfSight, true);
				GetBlackboardComponent()->SetValueAsBool(IsChasingEnemy, true);
				GetBlackboardComponent()->SetValueAsObject(EntityToChase, actor);
			}
			else if (actor == GetBlackboardComponent()->GetValueAsObject(EntityToChase))
			{
				GetBlackboardComponent()->SetValueAsBool(HasLineOfSight, false);
				GetBlackboardComponent()->SetValueAsVector(LastSeen, actor->GetActorLocation());
				GetBlackboardComponent()->ClearValue(EntityToChase);
			}
		}
	}
}

void AEntityController_Common::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(Entity_BT);
	SetPawn(InPawn);
	AEntityCharacter* entity = Cast<AEntityCharacter>(InPawn);
	Entity_BT = entity->Entity_BT;
	if (entity != nullptr)
	{
		currentWaypoint = entity->waypoint;
		GetBlackboardComponent()->SetValueAsObject(Waypoint, entity->waypoint);
		GetBlackboardComponent()->SetValueAsBool(IsMovingBB, entity->isMoving);
	}
}


