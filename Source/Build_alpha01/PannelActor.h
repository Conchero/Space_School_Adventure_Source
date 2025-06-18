// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PannelActor.generated.h"

/**
 *
 */
UCLASS()
class BUILD_ALPHA01_API APannelActor : public AStaticMeshActor
{
	GENERATED_BODY()
public:

	APannelActor();
	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxCollider;

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
		void  ShowText_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void  HideText_BP();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText TextToShow;
};
