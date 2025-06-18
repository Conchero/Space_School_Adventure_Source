// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectibles.generated.h"

UCLASS()
class BUILD_ALPHA01_API ACollectibles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibles();

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void PlayCollectSound();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite)
	bool canCollect;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void OnCollect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void CollectEffect(class AMainCharacter* _character);

	UFUNCTION(BlueprintImplementableEvent)
		void CollectEffect_BP(class AMainCharacter* _character);

	UFUNCTION(BlueprintImplementableEvent)
    void TimerBeforeCollect_BP();
};
