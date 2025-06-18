// Fill out your copyright notice in the Description page of Project Settings.


#include "HubLevelManager.h"
#include "Characters/MainCharacter.h"
#include "SingleDoor.h"

// Sets default values
AHubLevelManager::AHubLevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Trees.SetNum(5);
	/*for (UStaticMeshComponent* tree : Trees)
	{
		tree = CreateDefaultSubobject<UStaticMeshComponent>("tree");
	}*/
}

// Called when the game starts or when spawned
void AHubLevelManager::BeginPlay()
{
	Super::BeginPlay();


}

void AHubLevelManager::CheckLevels()
{

	AMainCharacter* character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), character->levelUnlocked.Num()));

	if (treeDoors.Num() <= character->levelUnlocked.Num() && character != nullptr && character->levelUnlocked.Num() != 0)
	{
		for (int i = 0; i < treeDoors.Num(); i++)
		{
			if (treeDoors[i] != nullptr)
			{
				treeDoors[i]->SetActorEnableCollision(!character->levelUnlocked[i]);
				treeDoors[i]->SetActorHiddenInGame(character->levelUnlocked[i]);
			}
		}
	}
}

// Called every frame
void AHubLevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



