// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrushingPillar.generated.h"

UCLASS()
class BUILD_ALPHA01_API ACrushingPillar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACrushingPillar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool crush = true;

	FVector basePos;
	UPROPERTY(EditAnywhere)
	float finalZValue;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* supportMesh;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* stickMesh;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* spikeMesh;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* damageBoxCollider;
	//UPROPERTY(EditAnywhere)
	//	class UBoxComponent* rightBoxCollider;
	//UPROPERTY(EditAnywhere)
	//	class UBoxComponent* frontBoxCollider;
	//UPROPERTY(EditAnywhere)
	//	class UBoxComponent* backBoxCollider;

	UPROPERTY(EditAnywhere)
	float speedCrush;
	UPROPERTY(EditAnywhere)
		float speedPullOut;

	UPROPERTY(EditAnywhere)
TEnumAsByte<EAxis::Type> _dirLaunch;

	UPROPERTY(EditAnywhere)
		TArray<class UStaticMeshComponent*> meshToMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;
	UFUNCTION(BlueprintImplementableEvent)
		void PlayCrushSound_BP();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CrushingPillarMovement(float DeltaTime);
	UFUNCTION()
	void OnCollisionDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void CollisionEffect(class AMainCharacter* _character);
};
