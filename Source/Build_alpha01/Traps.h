// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/Character.h>
#include "Traps.generated.h"

UCLASS()
class BUILD_ALPHA01_API ATraps : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraps();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EAxis::Type> launchCharacterDir;

	UFUNCTION()
		virtual void OnPlayerCollisionEnter(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//	virtual void OnPlayerCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* loopAudioComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool activated = false;
	//class USceneComponent* emptyParent;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxCollider;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;


	bool stun = true;
};
