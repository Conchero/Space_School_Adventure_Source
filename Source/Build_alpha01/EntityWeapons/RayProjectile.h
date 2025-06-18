// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RayProjectile.generated.h"

UCLASS()
class BUILD_ALPHA01_API ARayProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARayProjectile();

	UPROPERTY(EditAnywhere)
	float RayDuration;

	UPROPERTY(EditAnywhere)
	float RayDamage;

	UPROPERTY(EditAnywhere)
	AActor* Caster;

	UPROPERTY(EditAnywhere)
	class AEnnemie* castingEnemy;
	
	UPROPERTY(EditAnywhere)
	FVector InitPos;
	UPROPERTY(EditAnywhere)
	FVector GoalPos;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void LifeSpanExpired() override;
};
