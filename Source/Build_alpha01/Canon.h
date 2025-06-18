// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Canon.generated.h"

UCLASS()
class BUILD_ALPHA01_API ACanon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACanon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
		class USceneComponent* spawner;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> bullet;

	UPROPERTY(EditAnywhere)
		float timerCooldown;
	UPROPERTY(EditAnywhere)
		float timerOffset;
	float timer;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Shoot(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayShootSound_BP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;
};
