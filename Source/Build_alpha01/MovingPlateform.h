// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Climbable.h"
#include "GameFramework/Actor.h"
#include "BasicPlatform.h"
#include "MovingPlateform.generated.h"

//class FVector;

UENUM()
enum MovementPlatform
{
	TRANSLATE_RIGHT_FIRST UMETA(DisplayName = "Translate right first"),
	TRANSLATE_LEFT_FIRST UMETA(DisplayName = "Translate left first"),
	TRANSLATE_UP_FIRST UMETA(DisplayName = "Translate up first"),
	TRANSLATE_DOWN_FIRST UMETA(DisplayName = "Translate down first"),
	TRANSLATE_FORWARD_FIRST UMETA(DisplayName = "Translate forward first"),
	TRANSLATE_BACK_FIRST UMETA(DisplayName = "Translate back first"),

};

UCLASS()
class BUILD_ALPHA01_API AMovingPlateform : public AActor, public IClimbable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingPlateform();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementPlatform)
		TEnumAsByte<MovementPlatform> moveDir;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	const FVector* basePos;
	bool goRight;
	bool goLeft;
	bool goForward;
	bool goBack;
	bool goUp;
	bool goDown;
	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
	float distance;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHooverSound_BP();

};
