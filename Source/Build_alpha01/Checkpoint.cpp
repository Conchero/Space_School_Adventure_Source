// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Characters/MainCharacter.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//boxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	if (Cast<AMainCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMainCharacter::StaticClass())) != NULL)
	{
		lilly = Cast<AMainCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMainCharacter::StaticClass()));
	}

}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (lilly != nullptr)
	{
		distCheckpointLilly = (GetActorLocation() - lilly->GetActorLocation());
	
		/*GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Diff X = %f,Diff Z = %f"),distCheckpointLilly.X,distCheckpointLilly.Y));*/

		if (activated == false && distCheckpointLilly.Size() <= distToSave)
		{
			lilly->respawnCheckpointPos = GetActorLocation() - (GetActorForwardVector() * 100);
			lilly->CheckPointSave();
			activated = true;
			if (m_checkParticles != nullptr)
				UGameplayStatics::SpawnEmitterAttached(m_checkParticles, lilly->GetRootComponent());
				//UNiagaraFunctionLibrary::SpawnSystemAttached(m_checkParticles,lilly->GetRootComponent(),"",FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::KeepRelativeOffset,true);
		}

	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Checkpoint.cpp l 43: Lilly is null")));
	}
}

