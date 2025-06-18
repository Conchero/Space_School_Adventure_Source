// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectibles.h"
#include "MasterPiece.generated.h"

class UStaticMeshComponent;

UCLASS()
class BUILD_ALPHA01_API AMasterPiece : public ACollectibles
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere)
	//int32 index;

	//UPROPERTY(EditAnywhere)
	//TArray<class UStaticMeshComponent*> Trees; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* Root;

	virtual void CollectEffect(class AMainCharacter* _character) override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	UStaticMeshComponent* mesh;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Collect_BP(AActor* actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int numberLevel = 2;

	bool isCollect = false;
};
