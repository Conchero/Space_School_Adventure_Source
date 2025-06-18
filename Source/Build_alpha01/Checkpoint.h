// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class BUILD_ALPHA01_API ACheckpoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//class UBoxComponent* boxCollision;

	FVector distCheckpointLilly;
	bool activated;
	UPROPERTY(EditAnywhere)
	float distToSave = 500;

	UPROPERTY(EditAnywhere)
		class AMainCharacter* lilly;

	//UPROPERTY(EditAnywhere)
		//class UNiagaraSystem* m_checkParticles = nullptr;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* m_checkParticles = nullptr;
};
