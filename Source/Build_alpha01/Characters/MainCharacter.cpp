// Fill out your copyright notice in the Description page of Project Settings.
#include "MainCharacter.h"
#include "../BasicPlatform.h"
#include "../ClimbingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/Character.h>
#include <Runtime/AIModule/Classes/EnvironmentQuery/EQSTestingPawn.h>

#include "ChaosInterfaceWrapperCore.h"
#include "DrawDebugHelpers.h"
#include "../MovingPlateform.h"
#include "Kismet/GameplayStatics.h"
#include "../CharacterSaveManager.h"
#include "Slime.h"
#include "../SaveLoadManager.h"
#include "Perception/AISense_Hearing.h"
#include "../Sniper.h"
#include "../CarriableCube.h"
#include "../CameraShakeAttack.h"
#include "../Collectibles.h"
#include "../LouisCharacter.h"
#include <Components/AudioComponent.h>
#include "../MasterPiece.h"
#include "../EnemiesCountTriggerBox.h"

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UClimbingComponent>(ACharacter::CharacterMovementComponentName))
{
	//characterSaves = CreateDefaultSubobject<UCharacterSaveManager>("CharacterSaves");

	//if (characterSaves == nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Character saves component")));
	//}
	saveLoadManager = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass()));
	loopAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("loopAudioComponent"));
	loopAudioComponent->SetupAttachment(RootComponent);
	oneTimeAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("oneTimeAudioComponent"));
	oneTimeAudioComponent->SetupAttachment(RootComponent);
	//hitBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));

	//LouisCharacter = CreateDefaultSubobject<ALouisCharacter>(FName("LouisCharacter"));
	//LouisCharacter->SetupAttachment(RootComponent);


}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddUniqueDynamic(this, &AMainCharacter::GripToPlatform);
	//hitBoxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMainCharacter::HitColliderEffect);
	if (LouisCharacter != nullptr)
	{
		FVector LouisPosition = GetActorLocation() + (GetActorRightVector() * 50);
		ALouisCharacter* louis = GetWorld()->SpawnActor<ALouisCharacter>(LouisCharacter, LouisPosition, FRotator::ZeroRotator);
		louis->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false), "GrabSocket");
		louis->baseRotation = louis->GetActorRotation();
	}
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//FVector attachStartLocation = GetActorLocation() + (GetActorForwardVector() * 12) + (GetActorUpVector() * 40);
	//FVector attachEndRaycast = attachStartLocation + (GetActorForwardVector() * 25);
	//FVector headStartLocation = GetActorLocation() + (GetActorForwardVector() * 12) + (GetActorUpVector() * 70);
	//FVector headEndRaycast = headStartLocation + (GetActorForwardVector() * 25);

	//DrawDebugLine(GetWorld(), attachStartLocation, attachEndRaycast, FColor::Red);
	//DrawDebugLine(GetWorld(), headStartLocation, headEndRaycast, FColor::Red);
	if (GetMovementComponent()->Velocity.Size() > 0)
	{
		UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1.0, this);
	}

	/*if (GetMovementComponent()->Velocity.Size() > 0 && GetMovementComponent()->IsMovingOnGround() == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("is moving")));
	}*/
	CheckLanded();
	CheckGearLife();
	if (OneHealthLeftPlaying == true && m_health != 1)
	{
		StopOneHealthLeftSound_BP();
	}
	if (isLaundhedInAir)
	{
		timerLaunchFalse -= DeltaSeconds;
		if (timerLaunchFalse <= 0)
		{
			isLaundhedInAir = false;
			timerLaunchFalse = timerLaunchFalseValue;
		}
	}

	InputJump = false;
}


void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::UngripFromPlatform);
	PlayerInputComponent->BindAction("GroundPound", IE_Pressed, this, &AMainCharacter::GroundPound);
	/*if (characterSaves != nullptr)
	{
		PlayerInputComponent->BindAction("SaveCheckpoint", IE_Pressed, characterSaves, &UCharacterSaveManager::CheckPointSave);
		PlayerInputComponent->BindAction("LoadCheckpoint", IE_Pressed, characterSaves, &UCharacterSaveManager::CheckPointLoad);
	}*/
	//PlayerInputComponent->BindAction("SaveCheckpoint", IE_Pressed, this, &AMainCharacter::CheckPointSave);
	//PlayerInputComponent->BindAction("LoadCheckpoint", IE_Pressed, this, &AMainCharacter::CheckPointLoad);
	PlayerInputComponent->BindAction("SaveGame", IE_Pressed, this, &AMainCharacter::SaveGame);
	PlayerInputComponent->BindAction("LoadGame", IE_Pressed, this, &AMainCharacter::LoadGame);
	PlayerInputComponent->BindAction("ShowUI", IE_Pressed, this, &AMainCharacter::ShowUI_BP);

	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &AMainCharacter::Grab_BP);
}

void AMainCharacter::Jump()
{
	Super::Jump();
	if (GetMovementComponent()->Velocity.Size() > 0)
	{
		UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1.0, this);
	}

	if (JumpCurrentCount < GetCharacterMovement()->MaxJumpApexAttemptsPerSimulation)
	{
		isCrushing = false;
		GetCharacterMovement()->AirControl = baseAirControl;
	}
}
void AMainCharacter::CheckLanded()
{
	if (GetMovementComponent()->IsMovingOnGround() == true && wasInAirLastFrame == false)
	{
		PlayLandSound_BP();
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player")));

		if (isCrushing)
		{
			isCrushing = false;
			GetCharacterMovement()->AirControl = baseAirControl;
			PlayCrushLandSound_BP();
		}
	}

	wasInAirLastFrame = GetMovementComponent()->IsMovingOnGround();
}

void AMainCharacter::RemoveLife(int _lifePointToRemove, bool _stun, TEnumAsByte<EAxis::Type> _launchDir)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player life before %i"), m_health));
	if (IsHit == false)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartMatineeCameraShake(shake, 1.0f);

		m_health -= _lifePointToRemove;
		if (m_health == 1)
		{
			PlayOneHealthLeftSound_BP();
			OneHealthLeftPlaying = true;
		}
		else
		{
			StopOneHealthLeftSound_BP();
			OneHealthLeftPlaying = false;
		}
		if (m_health == 3)
		{
			maxHealth = 3;
		}
		FRotator rotator = GetActorRotation();
		FVector lanchDir = FRotationMatrix(rotator).GetScaledAxis(EAxis::X);
		LaunchCharacter(lanchDir * -2000, 0, 0);
		PlayHurtSound_BP();

		IsHit = true;

		LinkHitLayerAnimation();

		ShowHealthUI_BP();
		if (m_health <= 0)
		{
			ShowUI_BP();
			life -= 1;
			if (life <= 0)
			{
				GameOver_BP();
				//GetWorldTimerManager().SetTimer(timer, gameOverDelay, 3, false);
				//LoadGame();
			}
			else if (UGameplayStatics::DoesSaveGameExist("Checkpoint", 0) == true)
			{
				LooseLife_BP();
			/*	CheckPointLoad();
				ShowLifeUI_BP();*/
			}
			else
			{
				FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
				UGameplayStatics::OpenLevel(GetWorld(), FName(levelName));
			}
			//GetWorld()->GetCurrentLevel()->GetFName());
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player max life %i"), maxHealth));
}

void AMainCharacter::UngripFromPlatform()
{
	UClimbingComponent* climbingComponent = Cast<UClimbingComponent>(GetMovementComponent());
	if (climbingComponent != nullptr)
	{
		climbingComponent->UngripPlatform();
		isClimbing = false;
		climbingComponent->DetachPlayerFromPlatform();
	}

}

void AMainCharacter::GripToPlatform(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor != nullptr)
	{
		if (GetCharacterMovement()->IsMovingOnGround() == false && GetVelocity().Z < 0)
		{
			IClimbable* platform = Cast<IClimbable>(OtherActor);
			if (platform != nullptr)
			{
				//FVector attachStartLocation = GetActorLocation() + (GetActorForwardVector() * 14) + (GetActorUpVector() * 40);
				FVector attachStartLocation = GetActorLocation() + (GetActorForwardVector() * 14) + (GetActorUpVector() * 30);
				FVector attachEndRaycast = attachStartLocation + (GetActorForwardVector() * 25);
				FHitResult attachHit;
				GetWorld()->LineTraceSingleByChannel(attachHit, attachStartLocation, attachEndRaycast, ECollisionChannel::ECC_Visibility);

				//FVector headStartLocation = GetActorLocation() + (GetActorForwardVector() * 14) + (GetActorUpVector() * 70);
				FVector headStartLocation = GetActorLocation() + (GetActorForwardVector() * 14) + (GetActorUpVector() * 60);
				FVector headEndRaycast = headStartLocation + (GetActorForwardVector() * 25);
				FHitResult headHit;
				GetWorld()->LineTraceSingleByChannel(headHit, headStartLocation, headEndRaycast, ECollisionChannel::ECC_Visibility);


				if (attachHit.bBlockingHit == true && headHit.bBlockingHit == false)
				{

					UClimbingComponent* climbingComponent = Cast<UClimbingComponent>(GetMovementComponent());
					if (climbingComponent != nullptr)
					{
						climbingComponent->GripPlatform();
						isClimbing = true;
					}

					AMovingPlateform* movingPlateform = Cast<AMovingPlateform>(platform);
					if (movingPlateform != nullptr)
					{
						climbingComponent->AttachPlayerToPlatform(OtherActor);
					}
					else
					{

					}

				}

			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("couldn't cast to basic platform")));
			}
		}
	}

}

//
//void AMainCharacter::ShowUI()
//{
//		 hideGearUI = true;
//		 hideLifeUI = true;
//		 hideHealthUI = true;
//}

void AMainCharacter::CheckGearLife()
{
	if (gearCollected >= nextGearLife)
	{
		life++;
		gearCollected = 0;
		PlayOneUpSound_BP();
		ShowLifeUI_BP();
	}
}

void AMainCharacter::HitColliderEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Attacking && Cast<AEnnemie>(OtherActor) != nullptr)
	{

	}
}

void AMainCharacter::CheckPointSave()
{
	if (USaveLoadManager* SaveGameObject = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass())))
	{

		SaveGameObject->C_healthPoints = m_health;
		SaveGameObject->C_GearNumber = gearCollected;
		SaveGameObject->C_MaxHealth = maxHealth;
		SaveGameObject->C_Position = respawnCheckpointPos;
		SaveGameObject->C_Rotation = GetActorRotation();
		SaveAllCollectibles(SaveGameObject);
		SaveAllEnemies(SaveGameObject);

		FAsyncSaveGameToSlotDelegate asyncSave;
		asyncSave.BindUObject(this, &AMainCharacter::CheckPointSaveActions);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameObject, SaveGameObject->CheckpointSlot, 0, asyncSave);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MainCharacter.cpp l61: Save didn't worked ")));
	}
}

void AMainCharacter::CheckPointSaveActions(const FString& slotName, const int32 UserIndex, bool sucess)
{
	//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("Checkpoint Save")));
	PlayCheckpointTookSound_BP();
	PlayCheckpointTookUI_BP();
}

void AMainCharacter::CheckPointLoad()
{
	if (USaveLoadManager* SaveGameObject = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass())))
	{
		FAsyncLoadGameFromSlotDelegate asyncLoad;
		asyncLoad.BindUObject(this, &AMainCharacter::CheckPointLoadActions);

		UGameplayStatics::AsyncLoadGameFromSlot(SaveGameObject->CheckpointSlot, 0, asyncLoad);
	}


}

void AMainCharacter::CheckPointLoadActions(const FString& slotName, const int32 UserIndex, USaveGame* loadedGameData)
{
	if (USaveLoadManager* SaveGameTemp = Cast<USaveLoadManager>(loadedGameData))
	{

		m_health = SaveGameTemp->C_healthPoints;
		gearCollected = SaveGameTemp->C_GearNumber;
		maxHealth = SaveGameTemp->C_MaxHealth;
		SetActorLocation(SaveGameTemp->C_Position);
		SetActorRotation(SaveGameTemp->C_Rotation);
		LoadAllCollectibles(loadedGameData);
		LoadAllEnemies(loadedGameData);

		//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("Checkpoint Loaded")));
	}

}



void AMainCharacter::SaveGame()
{
	if (canSaveGame)
	{
		if (USaveLoadManager* SaveGameObject = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass())))
		{

			SaveGameObject->C_LifePoints = life;
			SaveGameObject->G_GearNumber = gearCollected;
			SaveGameObject->triggerEnd = triggerEnd;
			if (levelUnlocked.Num() != 0)
			{
				SaveGameObject->G_LevelUnlocked = levelUnlocked;
			}
			//SaveGameObject->G_Position = GetActorLocation();

			FAsyncSaveGameToSlotDelegate asyncSave;
			asyncSave.BindUObject(this, &AMainCharacter::SaveGameActions);
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameObject, SaveGameObject->GameSaveSlot, 0, asyncSave);
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MainCharacter.cpp 229: Save didn't worked ")));
		}
	}
}

void AMainCharacter::SaveGameActions(const FString& slotName, const int32 UserIndex, bool sucess)
{
	SaveEffect_BP();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Saved")));
}

void AMainCharacter::LoadGame()
{
	//UGameplayStatics::OpenLevel(GetWorld(), "Hub");
	if (USaveLoadManager* SaveGameObject = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass())))
	{
		FAsyncLoadGameFromSlotDelegate asyncLoad;
		asyncLoad.BindUObject(this, &AMainCharacter::LoadGameActions);

		UGameplayStatics::AsyncLoadGameFromSlot(SaveGameObject->GameSaveSlot, 0, asyncLoad);
	}


}

void AMainCharacter::LoadGameActions(const FString& slotName, const int32 UserIndex, class USaveGame* loadedGameData)
{
	if (USaveLoadManager* SaveGameTemp = Cast<USaveLoadManager>(loadedGameData))
	{
		life = SaveGameTemp->C_LifePoints;
		gearCollected = SaveGameTemp->G_GearNumber;
		triggerEnd = SaveGameTemp->triggerEnd;

		if (SaveGameTemp->G_LevelUnlocked.Num() != 0)
		{
			levelUnlocked = SaveGameTemp->G_LevelUnlocked;
		}
		//SetActorLocation(SaveGameTemp->G_Position);
		//SetActorRotation(FRotator::ZeroRotator);


		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), SaveGameTemp->G_LevelUnlocked[0]));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Loaded")));
	}
}

void AMainCharacter::SaveAllEnemies(USaveLoadManager* _SaveGame)
{
	if (_SaveGame != nullptr)
	{


		TArray<AActor*> tmp;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnnemie::StaticClass(), tmp);
		_SaveGame->enemiesClasses.SetNum(tmp.Num());
		_SaveGame->enemiesPosition.SetNum(tmp.Num());
		_SaveGame->slimeFactions.SetNum(tmp.Num());
		for (int i = 0; i < tmp.Num(); i++)
		{
			_SaveGame->enemiesClasses[i] = tmp[i]->GetClass();
			_SaveGame->enemiesPosition[i] = tmp[i]->GetActorLocation();
			_SaveGame->slimeFactions[i] = Cast<AEnnemie>(tmp[i])->FindComponentByClass<UFaction>();
		}



	}
}

void AMainCharacter::LoadAllEnemies(USaveGame* _loadedGameData)
{

	TArray<AActor*> enemiesInScene;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnnemie::StaticClass(), enemiesInScene);
	for (int i = 0; i < enemiesInScene.Num(); i++)
	{
		enemiesInScene[i]->Destroy();
	}
	if (USaveLoadManager* SaveGameTemp = Cast<USaveLoadManager>(_loadedGameData))
	{

		for (int i = 0; i < SaveGameTemp->enemiesClasses.Num(); i++)
		{
			GetWorld()->SpawnActor<AEnnemie>(SaveGameTemp->enemiesClasses[i], SaveGameTemp->enemiesPosition[i], FRotator::ZeroRotator);
		}

	}


}

void AMainCharacter::SaveAllCollectibles(class USaveLoadManager* _SaveGame)
{

	if (_SaveGame != nullptr)
	{
		TArray<AActor*> tmp;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectibles::StaticClass(), tmp);
		_SaveGame->collectibleClasses.SetNum(tmp.Num());
		_SaveGame->collectiblePosition.SetNum(tmp.Num());
		for (int i = 0; i < tmp.Num(); i++)
		{
			_SaveGame->collectibleClasses[i] = tmp[i]->GetClass();
			_SaveGame->collectiblePosition[i] = tmp[i]->GetActorLocation();
		}
	}

}

void AMainCharacter::LoadAllCollectibles(class USaveGame* loadedGameData)
{
	TArray<AActor*> collectibleInScene;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectibles::StaticClass(), collectibleInScene);

	for (int i = 0; i < collectibleInScene.Num(); i++)
	{
		if (Cast<AMasterPiece>(collectibleInScene[i]) == nullptr)
		{
			collectibleInScene[i]->Destroy();
		}
	}

	if (USaveLoadManager* SaveGameTemp = Cast<USaveLoadManager>(loadedGameData))
	{
		for (int i = 0; i < SaveGameTemp->collectibleClasses.Num(); i++)
		{
			
		   ACollectibles* objectSpawned = GetWorld()->SpawnActor<ACollectibles>(SaveGameTemp->collectibleClasses[i], SaveGameTemp->collectiblePosition[i], FRotator::ZeroRotator);
		   if (Cast<AMasterPiece>(objectSpawned) != nullptr)
		   {
			   objectSpawned->Destroy();
		   }
		}
	}

}

void AMainCharacter::SaveEnterLevel()
{
	if (USaveLoadManager* SaveGameObject = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass())))
	{

		SaveGameObject->C_LifePoints = life;
		SaveGameObject->G_GearNumber = gearCollected;

		FAsyncSaveGameToSlotDelegate asyncSave;
		asyncSave.BindUObject(this, &AMainCharacter::SaveEnterLevelActions);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameObject, SaveGameObject->EnterLevelSlot, 0, asyncSave);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MainCharacter.cpp 419: Save didn't worked ")));
	}

}

void AMainCharacter::SaveEnterLevelActions(const FString& slotName, const int32 UserIndex, bool sucess)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Saved")));
}

void AMainCharacter::LoadEnterLevel()
{
	if (USaveLoadManager* SaveGameObject = Cast<USaveLoadManager>(UGameplayStatics::CreateSaveGameObject(USaveLoadManager::StaticClass())))
	{
		FAsyncLoadGameFromSlotDelegate asyncLoad;
		asyncLoad.BindUObject(this, &AMainCharacter::LoadEnterLevelActions);

		UGameplayStatics::AsyncLoadGameFromSlot(SaveGameObject->EnterLevelSlot, 0, asyncLoad);
	}
}

void AMainCharacter::LoadEnterLevelActions(const FString& slotName, const int32 UserIndex, USaveGame* loadedGameData)
{
	if (USaveLoadManager* SaveGameTemp = Cast<USaveLoadManager>(loadedGameData))
	{
		life = SaveGameTemp->C_LifePoints;
		gearCollected = SaveGameTemp->G_GearNumber;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Loaded")));
	}
}

void AMainCharacter::GroundPound()
{
	if (JumpCurrentCount >= GetCharacterMovement()->MaxJumpApexAttemptsPerSimulation)
	{
		GetCharacterMovement()->AirControl = 0;
		FVector startLocation = GetActorLocation() + (GetActorUpVector() * (-40));
		FVector endRaycast = startLocation + (GetActorUpVector() * (-1000));
		FHitResult hit;
		GetWorld()->LineTraceSingleByChannel(hit, startLocation, endRaycast, ECollisionChannel::ECC_Visibility);

		if (hit.bBlockingHit == true)
		{
			if (isCrushing == false)
			{
				isCrushing = true;
				PlayCrushFallSound_BP();
			}
			FVector distFloorCharacter = hit.ImpactPoint - GetActorLocation();
			GEngine->AddOnScreenDebugMessage(-1, 25, FColor::Red, FString::Printf(TEXT("%f,%f,%f"), hit.ImpactNormal.X, hit.ImpactNormal.Y, hit.ImpactNormal.Z));
			GEngine->AddOnScreenDebugMessage(-1, 25, FColor::Blue, FString::Printf(TEXT("%f,%f,%f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z));
			GEngine->AddOnScreenDebugMessage(-1, 25, FColor::Green, FString::Printf(TEXT("%f,%f,%f"), distFloorCharacter.X, distFloorCharacter.Y, distFloorCharacter.Z));

			LaunchCharacter(distFloorCharacter * crushStrenghtMultiplier, true, true);

		}

	}
}

FVector AMainCharacter::GetRespawnCheckpointPos()
{
	return respawnCheckpointPos;
}

void AMainCharacter::CarryCube()
{


	//if (carriableCube == nullptr)
	//{
	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("nanana")));
	//	FVector startLocation = GetActorLocation() + (GetActorForwardVector() * 30) - (GetActorUpVector() * 30);
	//	FVector endRaycast = startLocation + (GetActorForwardVector() * 25);
	//	FHitResult Hit;
	//	GetWorld()->LineTraceSingleByChannel(Hit, startLocation, endRaycast, ECollisionChannel::ECC_Visibility);
	//	DrawDebugLine(GetWorld(), startLocation, endRaycast, FColor::Red);
	//	if (Hit.bBlockingHit == true)
	//	{
	//		if (Cast<ACarriableCube>(Hit.Actor) != nullptr)
	//		{
	//			carriableCube = Cast<ACarriableCube>(Hit.Actor);
	//			carriableCube->Grab(this);
	//			//carriableCube->character = this;
	//			//carriableCube->isCarried = !carriableCube->isCarried;
	//			
	//		}
	//	}
	//}
	//else
	//{
	//	carriableCube->isCarried = !carriableCube->isCarried;
	//	carriableCube = nullptr;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("leave")));

	//}



	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("in function ")));
	//if (carriableCube != nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("worked ")));
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" didn't worked ")));
	//}
}

int32 AMainCharacter::GetFirstDigitOfGears()
{
	if (gearCollected >= 10)
	{
		return gearCollected / 10;
	}
	else
	{
		return 0;
	}
}

int32 AMainCharacter::GetSecondDigitOfGears()
{

	return gearCollected % 10;

}

int32 AMainCharacter::GetFirstDigitEnemyCount()
{
	if (countTriggerIn != nullptr)
	{

		if (countTriggerIn->enemies.Num() >= 10)
		{
			return countTriggerIn->enemies.Num() / 10;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}

}

int32 AMainCharacter::GetSecondDigitEnemyCount()
{
	if (countTriggerIn != nullptr)
	{
		return countTriggerIn->enemies.Num() % 10;
	}
	else
	{
		return 0;
	}
}
