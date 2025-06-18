// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Climbable.h"
#include "BasicPlatform.generated.h"

UCLASS()
class BUILD_ALPHA01_API ABasicPlatform : public AActor, public IClimbable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StayGripped() override;

};
