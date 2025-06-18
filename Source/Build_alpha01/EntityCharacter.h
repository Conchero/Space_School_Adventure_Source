// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "EntityBullet.h"
#include "Faction.h"
#include "WaypointTool.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "EntityCharacter.generated.h"

UCLASS(Config=Game)
class BUILD_ALPHA01_API AEntityCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntityCharacter();

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	AWaypointTool* waypoint;

	UPROPERTY(EditAnywhere)
	UFaction* Faction;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	TArray<FName> Senses;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	UBehaviorTree* Entity_BT;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	float NeutralDistanceCall;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	bool isMoving;
	
	UPROPERTY()
	AActor* AttackInstigator;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEntityBullet> bullet;

	

protected:
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateWalkSpeed(float _newWalkSpeed);
};
