// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityCharacter.h"

#include "Faction.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEntityCharacter::AEntityCharacter()
{
	Faction = CreateDefaultSubobject<UFaction>(TEXT("Faction Component"));
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent* mesh : meshes)
	{
		mesh->SetCollisionObjectType(ECC_GameTraceChannel18);
	}
	
}

// Called when the game starts or when spawned
void AEntityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEntityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEntityCharacter::UpdateWalkSpeed(float _newWalkSpeed)
{
	this->GetCharacterMovement()->MaxWalkSpeed = _newWalkSpeed;
}

