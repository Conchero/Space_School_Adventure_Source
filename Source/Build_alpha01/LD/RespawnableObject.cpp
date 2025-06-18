// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnableObject.h"

// Sets default values
ARespawnableObject::ARespawnableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

// Called when the game starts or when spawned
void ARespawnableObject::BeginPlay()
{
	Super::BeginPlay();
	BeginLocation = GetActorLocation();
}

// Called every frame
void ARespawnableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARespawnableObject::RespawnObject()
{
	
	SetActorLocation(BeginLocation, false, nullptr, ETeleportType::ResetPhysics);
	StaticMesh->RecreatePhysicsState();
}

