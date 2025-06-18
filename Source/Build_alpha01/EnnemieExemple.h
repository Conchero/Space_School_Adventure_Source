// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Ennemie.h"
#include "EnnemieExemple.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API AEnnemieExemple : public AEnnemie
{
	GENERATED_BODY()
	
		virtual void Attack() override;

};
