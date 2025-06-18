// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSaveManager.generated.h"

class ASlime;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILD_ALPHA01_API UCharacterSaveManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterSaveManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class USaveLoadManager* saveLoadManager;

	UFUNCTION()
		void CheckPointSave();
	UFUNCTION()
		void CheckPointSaveActions(const FString& slotName, const int32 UserIndex, bool sucess);

	UFUNCTION()
		void CheckPointLoad();
	UFUNCTION()
		void CheckPointLoadActions(const FString& slotName, const int32 UserIndex, USaveGame* loadedGameData);


	void SaveAllEnemies(class USaveLoadManager* _SaveGame);
	UFUNCTION()
		void LoadAllEnemies(USaveGame* loadedGameData);
	class AMainCharacter* lilly;
	UPROPERTY(EditAnywhere, Category = "Prefabs")
		TSubclassOf<ASlime> neutralSlime;
	UPROPERTY(EditAnywhere, Category = "Prefabs")
		TSubclassOf<ASlime> agressiveSlime;




};
