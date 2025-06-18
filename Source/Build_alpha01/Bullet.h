// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class BUILD_ALPHA01_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int damage = 1;
	UPROPERTY(EditAnywhere)
		float speed = 1000.f;
	UPROPERTY(EditAnywhere)
		float gravityScale = 0;
	UPROPERTY(EditAnywhere)
		float lifeSpan = 10.f;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxCollider;

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* projectileMovementComponent;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EAxis::Type> launchCharacterDir;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void LaunchBullet();
	UFUNCTION()
		virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnJumpCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audioComponent;
	UFUNCTION(BlueprintImplementableEvent)
		void PlayExplodeSound_BP();
};
