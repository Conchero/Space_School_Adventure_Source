// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/CapsuleComponent.h>
#include <Components/BoxComponent.h>
#include <Camera/CameraComponent.h>
#include "PNJ_Pawn.generated.h"

UCLASS()
class BUILD_ALPHA01_API APNJ_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APNJ_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	USceneComponent* scene;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* capsuleCollision;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeletalMesh;

	UPROPERTY(EditAnywhere)
		UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		UBoxComponent* boxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isStatic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 indexOfList = 0;
};
