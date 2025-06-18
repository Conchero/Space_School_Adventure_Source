// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Faction.generated.h"

UENUM()
enum class FactionList : uint8
{
	AGGRESSIVE_ANIMALS UMETA(DisplayName = "Aggresive Animals"),
	NEUTRAL_ANIMALS	   UMETA(DisplayName = "Neutral Animals"),
	PASSIVE_ANIMALS    UMETA(DisplayName = "Passive Animals"),
	ROBOTS             UMETA(DisplayName = "Robots"),
	CORRUPTED_ROBOTS   UMETA(DisplayName = "Corrupted Robots"),
	PLAYER   UMETA(DisplayName = "Player")
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUILD_ALPHA01_API UFaction : public UActorComponent
{

	
	GENERATED_BODY()

public:


	
	// Sets default values for this component's properties
	UFaction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, Category = "Faction", BlueprintReadWrite)
	FactionList CurrentFaction;
	
	UPROPERTY(VisibleAnywhere, Category = "Faction", BlueprintReadWrite)
	TArray<FactionList> Allies;

	UPROPERTY(VisibleAnywhere, Category = "Faction", BlueprintReadWrite)
	TArray<FactionList> Neutral;

	UPROPERTY(VisibleAnywhere, Category = "Faction", BlueprintReadWrite)
	TArray<FactionList> Enemies;

	UPROPERTY(VisibleAnywhere, Category = "Faction", BlueprintReadWrite)
	TArray<FactionList> Afraid;

private:


};
