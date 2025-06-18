// Fill out your copyright notice in the Description page of Project Settings.


#include "CarriableCube.h"
#include "Characters/MainCharacter.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ACarriableCube::ACarriableCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACarriableCube::BeginPlay()
{
	Super::BeginPlay();
	//character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ACarriableCube::GetDistanceToPlayer()
{
	
}

void ACarriableCube::ChangeCarriable()
{

}

void ACarriableCube::CarryBehavior()
{

}

// Called every frame
void ACarriableCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (character != nullptr)
	//{
	//	mesh->ComponentVelocity = FVector(FVector::ZeroVector);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("grab")));
	//}
	//mesh->SetSimulatePhysics(!isCarried);
	//SetActorEnableCollision(!isCarried);
	//GetDistanceToPlayer();
	//ChangeCarriable();
	//CarryBehavior();
}

void ACarriableCube::Grab(class AMainCharacter* _character)
{
	/*character = _character;
	mesh->SetEnableGravity(false);
	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("grab")));*/
	//SetGravityEnable(false);
}

void ACarriableCube::Move(float _deltaTime)
{

}

