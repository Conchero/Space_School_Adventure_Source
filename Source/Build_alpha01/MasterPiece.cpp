// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterPiece.h"
#include "Characters/MainCharacter.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
AMasterPiece::AMasterPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AMasterPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterPiece::CollectEffect(class AMainCharacter* _character)
{
	Super::CollectEffect(_character);

	if (!isCollect)
	{
		isCollect = true;

		int nbLevelUnlocked = _character->levelUnlocked.Num();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), nbLevelUnlocked));
		_character->levelUnlocked.SetNum(nbLevelUnlocked + 1);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), _character->levelUnlocked.Num()));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), nbLevelUnlocked));
		_character->levelUnlocked[nbLevelUnlocked] = true;

		if (_character->levelUnlocked.Num() == numberLevel)
		{
			for (int i = 0; i < numberLevel; i++)
			{
				if (_character->levelUnlocked[i] == false)
				{
					break;
				}

				if (i == numberLevel - 1 && _character->levelUnlocked[numberLevel - 1] == true)
				{
					_character->triggerEnd = true;
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("lala")));
				}
			}
		}

		_character->canSaveGame = true;
		_character->SaveGame();

		Collect_BP(_character);
	}
}

//	Destroy();
