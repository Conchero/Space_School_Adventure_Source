// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleCrate.generated.h"

UCLASS()
class BUILD_ALPHA01_API ADestructibleCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleCrate();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
		void PlayDestroySound_BP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDestructibleComponent*  destructibleMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* boxCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* hitCollider;
	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnCollisionEffect(class AMainCharacter* _character);
	UFUNCTION(BlueprintImplementableEvent)
	void Destruction_BP(class AMainCharacter* _character);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UClass*> collectibleDrop;  

	UFUNCTION()
	void OnCrateHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int nbChoiceCollectible;


	UPROPERTY(EditAnywhere)
		int minGearDrop=1;

	UPROPERTY(EditAnywhere)
		int maxGearDrop=5;

	UFUNCTION()
	void CollectibleChoose();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int GearDropChance;
	//UFUNCTION(BlueprintImplementableEvent)
	//void DestructionHit_BP(class AMainCharacter* _character);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
