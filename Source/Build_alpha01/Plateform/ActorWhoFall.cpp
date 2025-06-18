// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWhoFall.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Characters/MainCharacter.h"

// Sets default values
AActorWhoFall::AActorWhoFall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	m_staticMesh->SetupAttachment(RootComponent);
	m_boxTrigger = CreateDefaultSubobject<UBoxComponent>(FName("BoxCol"));
	m_boxTrigger->SetupAttachment(m_staticMesh);
}

// Called when the game starts or when spawned
void AActorWhoFall::BeginPlay()
{
	Super::BeginPlay();

	m_boxTrigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &AActorWhoFall::OnColBeginOverlap);
	m_staticMesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &AActorWhoFall::OnColBeginOverlapInflicted);
}

void AActorWhoFall::OnColBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("OnColBeginOverlap")));
	AMainCharacter* character = Cast<AMainCharacter>(OtherActor);

	if (character != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("OnColBeginOverlap")));
		m_staticMesh->SetSimulatePhysics(true);
	}
}

//Déclenché par la zone de collision autour de l'actor qui infligera des dégats au player
void AActorWhoFall::OnColBeginOverlapInflicted(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("colid")));
	AMainCharacter* character = Cast<AMainCharacter>(OtherActor);

	if (character != nullptr)
	{
		//On fait appel à la fonction "remove life" du character
		character->RemoveLife(m_damage,true,launchCharacterDir);
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Colid with  character")));

		m_staticMesh->SetSimulatePhysics(false);
		//ICI On Déclanchera l'anim de destruction de l'objet, puis on le detruira
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Colid with another thing than character")));
		m_staticMesh->SetSimulatePhysics(false);
		//ICI On Déclanchera l'anim de destruction de l'objet, puis on le detruira
	}

	Destroy();
}


// Called every frame
void AActorWhoFall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

