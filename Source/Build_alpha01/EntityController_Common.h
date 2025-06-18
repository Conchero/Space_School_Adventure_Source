// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WaypointTool.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "EntityController_Common.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API AEntityController_Common : public AAIController
{
	GENERATED_BODY()
protected:
	AEntityController_Common();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "AI Sight Component")
	UAISenseConfig_Sight* EntitySightComponent;

	UPROPERTY(EditAnywhere, Category = "AI Hearing Component")
	UAISenseConfig_Hearing* EntityHearComponent;
	
	UPROPERTY(EditAnywhere, Category = "AI Damaged Component")
	UAISenseConfig_Damage* EntityDamagedComponent;
	
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* Entity_BT;
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName EntityToChase = "EntityToChase";
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName PatrolLocation = "PatrolLocation";
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName EntityActor = "EntityActor";
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName HasLineOfSight = "HasLineOfSight";
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName IsChasingEnemy = "IsChasingEnemy";
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName LastSeen = "LastSeen";
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName RemainingSearch = "RemainingSearch";
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName Waypoint = "Waypoint";
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	FName IsMovingBB = "IsMoving";

	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	bool IsMoving = true;




	UFUNCTION()
	void OnPerceptionUpdate(AActor* actor, FAIStimulus stimulus);
protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	UPROPERTY(VisibleAnywhere)
	AWaypointTool* currentWaypoint;
};
