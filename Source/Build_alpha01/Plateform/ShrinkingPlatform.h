// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShrinkingPlatform.generated.h"

UCLASS()
class BUILD_ALPHA01_API AShrinkingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShrinkingPlatform();



	UFUNCTION()
		void OnEnterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

   
	void Shrink(float _dt);

	void ResetValues();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxCollider;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		bool shrinkPlatfrom = false;
	UPROPERTY(EditAnywhere)
		float timerShrinkValue = 5;
	UPROPERTY(EditAnywhere)
		float timerShrink = timerShrinkValue;
	UPROPERTY(EditAnywhere)
		float timerRespawnValue = 5;
	UPROPERTY(EditAnywhere)
		float timerRespawn = timerRespawnValue;

	FVector baseScale;
	float reducingFactorX;
	float reducingFactorY;
	float reducingFactorZ;

	UFUNCTION(BlueprintImplementableEvent)
	void ShrinkPlatfrom_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void ResetPlatfromScale_BP();

	UPROPERTY(EditAnywhere)
		bool usingZ = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
