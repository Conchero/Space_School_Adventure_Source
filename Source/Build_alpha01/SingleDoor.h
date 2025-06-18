// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleDoor.generated.h"

UENUM()
enum DoorMovement
{
	ROTATE_CLOCKWISE UMETA(DisplayName = "Door rotate clockwise"),
	ROTATE_COUNTERCLOCK UMETA(DisplayName = "Door rotate counter clockwise"),
	TRANSLATE_VU UMETA(DisplayName = "Translate in vertical up"),
	TRANSLATE_VD UMETA(DisplayName = "Translate in vertical down"),
	TRANSLATE_HL UMETA(DisplayName = "Translate in horizontal left"),
	TRANSLATE_HR UMETA(DisplayName = "Translate in horizontal right"),
	TRANSLATE_HF UMETA(DisplayName = "Translate in horizontal forward"),
	TRANSLATE_HB UMETA(DisplayName = "Translate in horizontal back"),
	TRANSLATE_F UMETA(DisplayName = "Translate in forward"),
	TRANSLATE_R UMETA(DisplayName = "Translate in right"),
};

UCLASS()
class BUILD_ALPHA01_API ASingleDoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASingleDoor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayOpeningSound_BP();
	UFUNCTION(BlueprintImplementableEvent)
		void StopOpeningSound_BP();
	UPROPERTY(BlueprintReadWrite)
		bool OpeningSoundPlaying;


		const FRotator* doorBaseRot;
	const FVector* doorBasePos;
	bool activateBehaviour;

	UPROPERTY(EditAnywhere);
	float speedOpeningDoor;
	UPROPERTY(EditAnywhere);
	float speedClosingDoor;
	UPROPERTY(EditAnywhere);
	float rotationOfDoor;
	UPROPERTY(EditAnywhere);
	float translateOfDoor;
	UPROPERTY(EditAnywhere);
	TEnumAsByte<DoorMovement> doorMovement;

	void OpenDoor(float DeltaTime);


	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
