// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NinjaCharacter.h"
#include "../PNJ_Pawn.h"
#include "MainCharacter.generated.h"

class UCameraShakeAttack;

/**
 *
 */
UCLASS()
class BUILD_ALPHA01_API AMainCharacter : public ANinjaCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float BaseLookUpRate = 45.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float BaseTurnRate = 45.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SprintMultiplicator = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HitCooldownValue = 1.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HitCooldown = 1.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsHit = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool StunHit = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Attacking = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackTime = 0.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackCoolDownValue = 3.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackCoolDown = 3.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool DoCoolDown = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool CanDash = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dashing = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool OnBumper = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 gearCollected = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool canInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool inInteract;

	//Animation
	UPROPERTY(BlueprintReadWrite)
		bool isClimbing = false;

	//Allow to know if the jump is validate and going to be executed
	UPROPERTY(BlueprintReadWrite)
		bool InputJump = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 indexDialog = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 m_damage = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 maxHealth = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 m_health = maxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 life = 3;

	UPROPERTY(BlueprintReadWrite)
		class ACommandTriggerVolume* commandTrigger = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<bool> levelUnlocked;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
		bool activeCamera = true;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
		FVector springArmValue;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
		FRotator cameraValue;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShakeAttack> shake;

	UFUNCTION(BlueprintImplementableEvent)
		void GearFadeIn();
	UFUNCTION(BlueprintImplementableEvent)
		void GearFadeOut();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* loopAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* oneTimeAudioComponent;

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void LooseLife_BP();

private:
	AMainCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;
	virtual void Jump()override;

	class UCharacterSaveManager* characterSaves;

	bool wasInAirLastFrame = true;
	void CheckLanded();
	UPROPERTY(EditAnywhere)
		float timerLaunchFalseValue = 0.2f;
	float timerLaunchFalse = timerLaunchFalseValue;
public:
	UFUNCTION(BlueprintCallable)
		void RemoveLife(int _lifePointToRemove, bool _stun, TEnumAsByte<EAxis::Type> _dir);

	UFUNCTION(BlueprintImplementableEvent)
		void LinkHitLayerAnimation();

	UFUNCTION(BlueprintCallable)
		void GripToPlatform(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void UngripFromPlatform();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayImpactSound_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayCrushFallSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayCrushLandSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayCheckpointTookSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayCheckpointTookUI_BP();

	UPROPERTY(BlueprintReadWrite)
		bool ShowSaveFX;
protected:

	UFUNCTION(BlueprintImplementableEvent)
		void PlayOneHealthLeftSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void StopOneHealthLeftSound_BP();
	UPROPERTY(BlueprintReadWrite)
		bool OneHealthLeftPlaying = false;


	UFUNCTION(BlueprintImplementableEvent)
		void PlayHurtSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayLandSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayOneUpSound_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowHealthUI_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowLifeUI_BP();


	UFUNCTION(BlueprintImplementableEvent)
		void SaveEffect_BP();

	UPROPERTY(EditAnywhere)
		int nextGearLife = 100;

	UFUNCTION(BlueprintImplementableEvent)
		void ShowUI_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void Grab_BP();

	UPROPERTY(BlueprintReadWrite)
		bool GrabbingCarriableObject = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float crushStrenghtMultiplier = 3.f;



	void CheckGearLife();
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitBoxCollider;
	UFUNCTION()
		virtual void HitColliderEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool triggerEnd = false;

	UPROPERTY(BlueprintReadWrite)
		bool isLaundhedInAir = false;
	UFUNCTION(BlueprintImplementableEvent)
		void LaunchBoolManager_BP();
	UPROPERTY(BlueprintReadWrite)
		class AEnemiesCountTriggerBox* countTriggerIn;


	UPROPERTY(BlueprintReadWrite)
		bool isCrushing = false;

	class USaveLoadManager* saveLoadManager;

	UFUNCTION()
		void CheckPointSave();
	UFUNCTION()
		void CheckPointSaveActions(const FString& slotName, const int32 UserIndex, bool sucess);

	UFUNCTION(BlueprintCallable)
		void CheckPointLoad();
	UFUNCTION()
		void CheckPointLoadActions(const FString& slotName, const int32 UserIndex, class USaveGame* loadedGameData);

	UPROPERTY(BlueprintReadWrite)
		bool canSaveGame;

	UFUNCTION(BlueprintCallable)
		void SaveGame();
	UFUNCTION()
		void SaveGameActions(const FString& slotName, const int32 UserIndex, bool sucess);

	UFUNCTION(BlueprintCallable)
		void LoadGame();
	UFUNCTION()
		void LoadGameActions(const FString& slotName, const int32 UserIndex, class USaveGame* loadedGameData);

	void SaveAllEnemies(class USaveLoadManager* _SaveGame);
	UFUNCTION()
		void LoadAllEnemies(class USaveGame* loadedGameData);

	void SaveAllCollectibles(class USaveLoadManager* _SaveGame);
	UFUNCTION()
		void LoadAllCollectibles(class USaveGame* loadedGameData);

	UFUNCTION(BlueprintCallable)
		void SaveEnterLevel();
	UFUNCTION()
		void SaveEnterLevelActions(const FString& slotName, const int32 UserIndex, bool sucess);
	UFUNCTION(BlueprintCallable)
		void LoadEnterLevel();
	UFUNCTION()
		void LoadEnterLevelActions(const FString& slotName, const int32 UserIndex, class USaveGame* loadedGameData);


	UFUNCTION()
		void GroundPound();


	//bool ComeFromLevel;

	UPROPERTY(EditAnywhere, Category = "Prefabs")
		TSubclassOf<class ASlime> neutralSlime;
	UPROPERTY(EditAnywhere, Category = "Prefabs")
		TSubclassOf<class ASlime> agressiveSlime;
	UPROPERTY(EditAnywhere, Category = "Prefabs")
		TSubclassOf<class ASniper> agressiveSniper;

	FVector respawnCheckpointPos;

	UFUNCTION(BlueprintCallable)
		FVector GetRespawnCheckpointPos();

	UPROPERTY(EditAnywhere)
		float baseAirControl = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ALouisCharacter> LouisCharacter;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hideGearUI = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hideLifeUI = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hideHealthUI = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ACarriableCube* carriableCube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float grabDistance = 300;

	UFUNCTION()
		void CarryCube();

	UFUNCTION(BlueprintCallable)
		int32 GetFirstDigitOfGears();

	UFUNCTION(BlueprintCallable)
		int32 GetSecondDigitOfGears();

	UFUNCTION(BlueprintCallable)
		int32 GetFirstDigitEnemyCount();

	UFUNCTION(BlueprintCallable)
		int32 GetSecondDigitEnemyCount();
};
