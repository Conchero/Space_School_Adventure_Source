// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include <Containers/UnrealString.h>
#include "SaveLoadManager.generated.h"

/**
 * 
 */
UCLASS()
class BUILD_ALPHA01_API USaveLoadManager : public USaveGame
{
	GENERATED_BODY()
public:

	FString CheckpointSlot = "Checkpoint";

	UPROPERTY()
		FString C_CurrentLevelName;
	UPROPERTY()
		FVector C_Position;
	UPROPERTY()
		FRotator C_Rotation;
	UPROPERTY()
		int C_GearNumber;
	UPROPERTY()
		int C_healthPoints;
	UPROPERTY()
		int C_LifePoints;
	UPROPERTY()
		int C_MaxHealth;

	UPROPERTY()
		TArray<UClass*> enemiesClasses;
	UPROPERTY()
		TArray<FVector> enemiesPosition;
	UPROPERTY()
		TArray<class UFaction*> slimeFactions;

	UPROPERTY()
		TArray<UClass*> collectibleClasses;
	UPROPERTY()
		TArray<FVector> collectiblePosition;


	UPROPERTY()
		FString GameSaveSlot = "GameSave";
	UPROPERTY()
		FVector G_Position;
	UPROPERTY()
		int G_GearNumber;
	UPROPERTY()
		int G_LifeRemaining;
	UPROPERTY()
		TArray<bool> G_LevelUnlocked;
	UPROPERTY()
		bool triggerEnd;


	UPROPERTY()
		FString EnterLevelSlot = "EnterLevel";
};
