// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorWhoFall.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
UCLASS()
class BUILD_ALPHA01_API AActorWhoFall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorWhoFall();

	//properties
	//UPROPERTY(EditAnywhere)
		//float m_fallSpeed = 300.0f;

protected:

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EAxis::Type> launchCharacterDir;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//properties
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_staticMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* m_boxTrigger;

	//Valeur par defaut qui sera défini dans les classes enfants
	UPROPERTY(EditAnywhere)
		int32 m_damage = 1;

	//Déclenché par la zone de trigger qui fera tomber l'actor
	UFUNCTION()
		void OnColBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Déclenché par la zone de collision autour de l'actor qui infligera des dégats au player
	UFUNCTION()
		void OnColBeginOverlapInflicted(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
