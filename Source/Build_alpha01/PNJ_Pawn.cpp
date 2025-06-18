// Fill out your copyright notice in the Description page of Project Settings.


#include "PNJ_Pawn.h"

// Sets default values
APNJ_Pawn::APNJ_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	scene->SetupAttachment(RootComponent);

	capsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	capsuleCollision->SetupAttachment(scene);
	capsuleCollision->SetRelativeLocation(FVector(0, 0, 60));
	capsuleCollision->SetRelativeScale3D(FVector(0.7, 0.7, 0.7));
	capsuleCollision->SetCapsuleHalfHeight(88);
	capsuleCollision->SetCapsuleRadius(34);
	capsuleCollision->SetCollisionProfileName("Pawn");

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(capsuleCollision);
	camera->SetRelativeLocation(FVector(215.5, 0, 173));
	camera->SetRelativeRotation(FRotator(-30, -180, 0));

	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	skeletalMesh->SetupAttachment(capsuleCollision);
	skeletalMesh->SetRelativeLocation(FVector(0, 0, -95));
	skeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	boxCollision->SetupAttachment(skeletalMesh);
	boxCollision->SetRelativeLocation(FVector(0, 0, 95));
	boxCollision->SetRelativeRotation(FRotator(0, 90, 0));
	boxCollision->SetBoxExtent(FVector(150, 150, 100));
}

// Called when the game starts or when spawned
void APNJ_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APNJ_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APNJ_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

