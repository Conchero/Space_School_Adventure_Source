// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/Ennemie.h"
#include "LouisCharacter.generated.h"



UCLASS()
class BUILD_ALPHA01_API ALouisCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALouisCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
    class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
    class UBoxComponent* boxCollider;



	UPROPERTY(EditAnywhere)
	float timerShockValue = 5;
	float timerShock = timerShockValue;
	float distToLouis = 1000000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSplinePlayingFwd = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAttackPlayingFwd = false;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ATKImpulseEvent(AEnnemie* _enemy, FRotator _lookAtRotation);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;
	UFUNCTION(BlueprintImplementableEvent)
    void PlaySoundAttack_BP();
	UPROPERTY(BlueprintReadWrite)
		FRotator baseRotation;
};
