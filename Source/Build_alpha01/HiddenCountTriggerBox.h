// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HiddenCountTriggerBox.generated.h"

UCLASS()
class BUILD_ALPHA01_API AHiddenCountTriggerBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHiddenCountTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> actorsToCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> actorsToVisible;
};
