// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class BUILD_ALPHA01_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		//exemple de stockage de reference d'objet :
		//
		//		TArray<AInteractible*> m_interactibles;
		//public:
		//	// Called every frame.
		//	virtual void BeginPlay() override;
		//	virtual void Tick(float DeltaSeconds) override;
		//
		//	void PrintNomberOfInteractibleLess();
		//Fin d'exemple
};
