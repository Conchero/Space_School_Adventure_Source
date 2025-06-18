// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingPlatform.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class BUILD_ALPHA01_API AFallingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFallingPlatform();
	UPROPERTY(EditAnywhere)
		UBoxComponent* boxCollider;
	UPROPERTY(EditAnywhere)
	UBoxComponent* platformCollider;
	UStaticMeshComponent* staticMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void FallingBehaviourEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void FallingBehaviourExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ResetValues();

	bool playerOnPlatform;
	bool platformFalling;
	bool readyToRespawn;

	float timerBeforeFall;
	float timerBeforeRespawn;

	const FVector* basePos;
	float speed;
	float distance;


	const FRotator* baseRot;
	UPROPERTY(EditAnywhere)
		float speedShaking;
	UPROPERTY(EditAnywhere)
		float shakingOffset;
	bool shakeRight;

	//ApplyDownwardsForce();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool playShakeSound = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;
	UFUNCTION(BlueprintImplementableEvent)
		void PlayShakingSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void StopShakingSound_BP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool playFallSound = false;
	UFUNCTION(BlueprintImplementableEvent)
		void PlayFallSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void StopFallSound_BP();




};
