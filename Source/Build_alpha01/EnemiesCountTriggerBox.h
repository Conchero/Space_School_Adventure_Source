// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemiesCountTriggerBox.generated.h"

UCLASS()
class BUILD_ALPHA01_API AEnemiesCountTriggerBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemiesCountTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*>enemies;
	TArray<AActor*>player;
	AMainCharacter* playerIn;
	class UBoxComponent* triggerBox;

	
	UPROPERTY(BlueprintReadWrite)
	bool showWidgetEnemyCount;

	UPROPERTY(EditAnywhere)
		TArray<class ASingleDoor*> doorToOpen;

	UPROPERTY(BlueprintReadOnly)
	bool activateBehaviour;

};
