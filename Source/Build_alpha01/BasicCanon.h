// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Canon.h"
#include "BasicCanon.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API ABasicCanon : public ACanon
{
	GENERATED_BODY()
	
public:
	ABasicCanon();

	 void BeginPlay()override ;
	 void Tick(float DeltaTime)override ;
};
