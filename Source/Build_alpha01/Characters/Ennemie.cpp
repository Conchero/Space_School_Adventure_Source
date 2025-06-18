// Fill out your copyright notice in the Description page of Project Settings.


#include "Ennemie.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
//#include "C:/Program Files/Epic Games/UE_4.26/Engine/Plugins/Marketplace/NinjaCharacter/Source/NinjaCharacter/Public/NinjaCharacter.h"
#include "MainCharacter.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../CameraShakeAttack.h"
#include "../LouisCharacter.h"
#include <Particles/ParticleSystemComponent.h>

void AEnnemie::OnConstruction(const FTransform& Transform)
{
	/*if (m_boxComponent != nullptr && RootComponent != nullptr)
	{
		FAttachmentTransformRules TransformRule(EAttachmentRule::KeepRelative, false);
		TransformRule.LocationRule = EAttachmentRule::KeepRelative;
		TransformRule.RotationRule = EAttachmentRule::KeepRelative;
		TransformRule.ScaleRule = EAttachmentRule::KeepWorld;

		m_boxComponent->AttachToComponent(RootComponent, TransformRule);
	}*/
}

// Sets default values
AEnnemie::AEnnemie()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_boxColDmgSuffered = CreateDefaultSubobject<UBoxComponent>(FName("BoxColDmgSuffered"));
	m_boxColDmgSuffered->SetupAttachment(RootComponent);
	m_boxColDmgInflicted = CreateDefaultSubobject<UBoxComponent>(FName("BoxColDmgInflicted"));
	m_boxColDmgInflicted->SetupAttachment(RootComponent);
	audioComponent = CreateDefaultSubobject<UAudioComponent>(FName("audioComponent"));
	audioComponent->SetupAttachment(RootComponent);
	loopAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("loopAudio"));
	loopAudioComponent->SetupAttachment(RootComponent);
	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>("particleSystem");
	particleSystem->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnnemie::BeginPlay()
{
	Super::BeginPlay();
	particleSystem->SetVisibility(false);
	//m_staticMesh->SetRelativeLocation(FVector(0, 0, 0));
	//	m_boxComponent->SetRelativeLocation(FVector(0, 0, 99));
//	m_boxComponent->SetRelativeLocation(FVector(0, 200, 0));

	//m_boxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	m_boxColDmgSuffered->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnnemie::OnColBeginOverlapSuffered);
	m_boxColDmgInflicted->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnnemie::OnColBeginOverlapInflicted);
	//IsFreezed = true;
}

//Gestion de la collision avec le player au dessus de l'ennemi, inflige des degats à l'ennemie et fait decoller le player du sol
void AEnnemie::OnColBeginOverlapSuffered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("colidSuffered")));
	AMainCharacter* character = Cast<AMainCharacter>(OtherActor);

	if (character != nullptr)
	{
		if (character->GetCharacterMovement()->IsMovingOnGround() == false)
		{
			PlayJumpHurtSound_BP();
			FVector velocity(FVector::UpVector * throwForce);
			if (character->isCrushing == false)
			{
				if (character->isLaundhedInAir == false)
				{
					character->LaunchCharacter(velocity, 0, 0);
					character->isLaundhedInAir = true;
					character->LaunchBoolManager_BP();
				}
				else
				{
				}

			}
			RemoveLife(1.f, character);

		}


	}
}
//Gestion de la collision avec le player autour de l'ennemie, inflige des degats au player 
void AEnnemie::OnColBeginOverlapInflicted(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("colidInflicted")));
	AMainCharacter* character = Cast<AMainCharacter>(OtherActor);

	if (character != nullptr)
	{
		//Une fois le character cast 
		//On verifie la variable "Attacking" du character
		//=>si elle est true, on fait perdre de la vie à l'ennemie
	    if (character->Attacking)
		{
			PlayAttackHurtSound_BP();
			RemoveLife(character->m_damage, character);
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Ennemi life %i"), m_health));
		}
		//=> si elle est false
		else
		{
			//On verifie la variable "hit ennemie" du character
			//=> Si elle est false,
			if (!character->IsHit)
			{
				//	//on fait un launch character depuis le character :
				//	//en paramettre "launch velocity", on recupère la rotation du character avec un "GetActorRotation", 
				//	FRotator rotator(character->GetActorRotation());
				//	//depuis laquel	on fait un "get forward vector",
				//	FVector launchVelocity(FRotationMatrix(rotator).GetScaledAxis(EAxis::X));
				//	// on multiply le résultat par -2000, on donne cette valeur final en paramettre
				//	character->LaunchCharacter(launchVelocity * -2000.0f, 0, 0);

				//	//On set la variable "hit ennemie" du charactere à true,
				//	character->IsHit = true;

				//	// et la variable "is Hit" du character à false
				//	character->StunHit = false;

				//	//On fait ensuite appel à la fonction "remove life" du character
				character->PlayImpactSound_BP();
				character->RemoveLife(m_damage, true, launchCharacterDir);
				//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player life %i"), character->m_health));
			}
		}
	}
}

// Called every frame
void AEnnemie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsFreezed)
	{
		GetController()->StopMovement();
		freezeTimer -= DeltaTime;
		if (freezeTimer <= 0)
		{
			HideElectricField();
			IsFreezed = false;
			freezeTimer = freezeTimerValue;
		}
	}
}

// Called to bind functionality to input
void AEnnemie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnnemie::Attack()
{
	//Code qui g�re les comportements d'attaques generalis� pour tous les ennemies


}



void AEnnemie::RemoveLife(int _lifePointToRemove, AActor* _instigator)
{
	m_health -= _lifePointToRemove;
	AttackInstigator = _instigator;
	UAISense_Damage::ReportDamageEvent(GetWorld(), this, _instigator, _lifePointToRemove, GetActorLocation(), GetActorLocation());
	if (m_health <= 0)
	{
		if (m_deathParticles != nullptr)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, m_deathParticles, GetActorLocation());
		}
		this->SetLifeSpan(0.01f);
		if (FMath::RandRange(0.f, 100.f) <= healthDropChance)
		{
			GetWorld()->SpawnActor(m_prefabHealth, &GetTransform());
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Play")));
		}
		else
		{
			GetWorld()->SpawnActor(m_prefabPieces, &GetTransform());
		}
	}
	else
	{
		if (m_hitParticles != nullptr)
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, m_hitParticles, GetActorLocation());
	}

	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartMatineeCameraShake(shake, 1.0f);
}

float AEnnemie::GetDistanceWithLouis()
{
	if (louis != nullptr)
	{
		FVector distToPlayer = louis->GetActorLocation() - GetActorLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%f"), distToPlayer.Size()));
		return distToPlayer.Size();

	}
	else
	{
		return 0.0f;
	}
}

void AEnnemie::ShowElectricField()
{
	IsFreezed = true;
	particleSystem->SetVisibility(IsFreezed);
}

void AEnnemie::HideElectricField()
{
	IsFreezed = false;
	particleSystem->SetVisibility(IsFreezed);
}

