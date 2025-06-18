// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HubLevelManager.generated.h"

UCLASS()
class BUILD_ALPHA01_API AHubLevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHubLevelManager();

	UFUNCTION(BlueprintCallable)
	void CheckLevels();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	int32 index;
	UPROPERTY(EditAnywhere)
	TArray<class ASingleDoor*> treeDoors;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
