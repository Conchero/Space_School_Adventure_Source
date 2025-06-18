// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushButton.generated.h"

UENUM()
enum ButtonType
{
	COUNT_DOWN UMETA(DisplayName = "Have a countdown"),
	NO_COUNTDOWN UMETA(DisplayName = "Don't have a countdown"),
};

UCLASS()
class BUILD_ALPHA01_API APushButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APushButton();

	class UBoxComponent* collider;

	UFUNCTION()
		void PushButtonBehaviourEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void PushButtonBehaviourExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool buttonPressed;
	UPROPERTY(BlueprintReadOnly)
	bool activateBehaviour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementPlatform)
		TEnumAsByte<ButtonType> buttonType;


	const FVector* basePos;

	UPROPERTY(EditInstanceOnly)
		float speed;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	AActor* triggeredActor;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
