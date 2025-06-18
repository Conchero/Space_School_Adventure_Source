// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveLoadManager.h"
#include "Characters/MainCharacter.h"
#include "Characters/Ennemie.h"
#include "Characters/Slime.h"
#include "Faction.h"
#include "GameFramework/Actor.h"
// Sets default values for this component's properties
UCharacterSaveManager::UCharacterSaveManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UCharacterSaveManager::BeginPlay()
{
	Super::BeginPlay();
	saveLoadManager = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass()));
	lilly = Cast<AMainCharacter>(GetOwner());
	if (lilly == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Character Save Manager.cpp l:32 ,lilly doesn't work ")));
	}


	// ...

}

void UCharacterSaveManager::CheckPointSave()
{
	if (USaveLoadManager* SaveGameObject = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass())))
	{
		SaveGameObject->C_healthPoints = lilly->m_health;
		SaveGameObject->C_GearNumber = lilly->gearCollected;
		SaveGameObject->C_Position = lilly->GetActorLocation();
		SaveGameObject->C_Rotation = lilly->GetActorRotation();
		SaveAllEnemies(SaveGameObject);

		FAsyncSaveGameToSlotDelegate asyncSave;
		asyncSave.BindUObject(this, &UCharacterSaveManager::CheckPointSaveActions);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameObject, TEXT("Checkpoint"), 0, asyncSave);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MainCharacter.cpp l61: Save didn't worked ")));
	}
}

void UCharacterSaveManager::CheckPointSaveActions(const FString& slotName, const int32 UserIndex, bool sucess)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SaveCreated")));
}

void UCharacterSaveManager::CheckPointLoad()
{

	FAsyncLoadGameFromSlotDelegate asyncLoad;
	asyncLoad.BindUObject(this, &UCharacterSaveManager::CheckPointLoadActions);

	UGameplayStatics::AsyncLoadGameFromSlot("Checkpoint", 0, asyncLoad);

}

void UCharacterSaveManager::CheckPointLoadActions(const FString& slotName, const int32 UserIndex, USaveGame* loadedGameData)
{
	if (USaveLoadManager* SaveGameTemp = Cast<USaveLoadManager>(loadedGameData))
	{

		lilly->m_health = SaveGameTemp->C_healthPoints;
		lilly->gearCollected = SaveGameTemp->C_GearNumber;
		lilly->SetActorLocation(SaveGameTemp->C_Position);
		lilly->SetActorRotation(SaveGameTemp->C_Rotation);

		LoadAllEnemies(loadedGameData);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Loaded")));
	}

}

void UCharacterSaveManager::SaveAllEnemies(USaveLoadManager* _SaveGame)
{
	





}

void UCharacterSaveManager::LoadAllEnemies(USaveGame* _loadedGameData)
{
	
}
// Called every frame
void UCharacterSaveManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

