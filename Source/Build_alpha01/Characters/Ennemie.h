// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EntityCharacter.h"
#include "GameFramework/Character.h"
#include "Ennemie.generated.h"


class UBoxComponent;
class ACharacter;
//class ANinjaCharacter;
class AMainCharacter;
class UCameraShakeAttack;

UCLASS()
class BUILD_ALPHA01_API AEnnemie : public AEntityCharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AEnnemie();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* loopAudioComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayRobotAttackSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayRobotExplodeSound_BP();
protected:
	UPROPERTY(EditAnywhere)
		int m_health = 3.0;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EAxis::Type> launchCharacterDir;
	//ACharacterBP* m_asCharacterBP;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayAttackHurtSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayJumpHurtSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void EnemyHitPlayer_BP();

	//UPROPERTY(EditAnywhere)
	//	//component
	//	UStaticMeshComponent* m_staticMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* m_boxColDmgSuffered;

	UPROPERTY(EditAnywhere)
		UBoxComponent* m_boxColDmgInflicted;

	UPROPERTY(EditAnywhere)
		UClass* m_prefabPieces;

	UPROPERTY(EditAnywhere)
		UClass* m_prefabHealth;

	//Valeur par defaut qui sera défini dans les classes enfants
	UPROPERTY(EditAnywhere)
		int32 m_damage = 1;

	UPROPERTY(EditAnywhere)
		float m_speed = 1;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* m_hitParticles = nullptr;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* m_deathParticles = nullptr;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UFUNCTION()
		//void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnColBeginOverlapSuffered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnColBeginOverlapInflicted(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		float healthDropChance = 20.f;
	
	UPROPERTY(EditAnywhere)
    float throwForce = 800;

	UPROPERTY(EditAnywhere)
    class UParticleSystemComponent* particleSystem;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Attack();

	

	UFUNCTION(BlueprintCallable)
	void RemoveLife(int _lifePointToRemove, AActor* _instigator);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeAttack> shake;

	class ALouisCharacter* louis;

	float GetDistanceWithLouis();

	bool IsFreezed = false;

	UPROPERTY(EditAnywhere)
	float freezeTimerValue =  2.f;
	float freezeTimer = freezeTimerValue;
	UFUNCTION(BlueprintCallable)
	void ShowElectricField();
	void HideElectricField();

	
};
