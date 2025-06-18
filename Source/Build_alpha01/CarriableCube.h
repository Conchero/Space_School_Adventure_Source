// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarriableCube.generated.h"

UCLASS()
class BUILD_ALPHA01_API ACarriableCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarriableCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetDistanceToPlayer();
	void ChangeCarriable();
	void CarryBehavior();

	float distToPlayer;
	UPROPERTY(EditAnywhere)
	float carryDistance = 50;


UPROPERTY(EditAnywhere, BlueprintReadWrite)
class UStaticMeshComponent* mesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool isCarried;

	class	AMainCharacter* character;

	void Grab(class AMainCharacter* _character);

	void Move(float _deltaTime);
};
