// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrinkingPlatform.h"
#include <Components/BoxComponent.h>
#include "../Characters/MainCharacter.h"

// Sets default values
AShrinkingPlatform::AShrinkingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	boxCollider = CreateDefaultSubobject<UBoxComponent>("boxCollider");
	mesh->SetupAttachment(RootComponent);
	boxCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShrinkingPlatform::BeginPlay()
{
	Super::BeginPlay();
	baseScale = RootComponent->GetRelativeScale3D();
	 reducingFactorX = RootComponent->GetRelativeScale3D().X / (timerShrinkValue*60);
	 reducingFactorY = RootComponent->GetRelativeScale3D().Y / (timerShrinkValue*60);
	 reducingFactorZ = RootComponent->GetRelativeScale3D().Z / (timerShrinkValue * 60);

	 //GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("%f"), reducingFactorX));
	 //GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("%f"), reducingFactorY));
	 if (boxCollider != nullptr)
	 {
		 boxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AShrinkingPlatform::OnEnterOverlap);
	 }
	 else
	 {
		 //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("boxColliderNull")));
	 }
	 mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	
}

void AShrinkingPlatform::OnEnterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor) != nullptr)
	{
		shrinkPlatfrom = true;
	}
}



void AShrinkingPlatform::Shrink(float _dt)
{

	if (shrinkPlatfrom)
	{

		if (timerShrink > 0)
		{
			timerShrink -= _dt;
	
	
			if (RootComponent->GetRelativeScale3D().Size() > 0)
			{
				if (usingZ)
				{
					RootComponent->SetRelativeScale3D(FVector(RootComponent->GetRelativeScale3D().X - reducingFactorX, RootComponent->GetRelativeScale3D().Y - reducingFactorY, RootComponent->GetRelativeScale3D().Z - reducingFactorZ));
				}
				else
				{
					RootComponent->SetRelativeScale3D(FVector(RootComponent->GetRelativeScale3D().X - reducingFactorX, RootComponent->GetRelativeScale3D().Y - reducingFactorY, RootComponent->GetRelativeScale3D().Z));
				}
			}
			else
			{
			
			}
		
		
		}
		else
		{
			timerRespawn -= _dt;
			if (timerRespawn <= 0)
			{
				RootComponent->SetRelativeScale3D(FVector(baseScale));
				ResetValues();
			}
			else
			{
				//ShrinkPlatfrom_BP();
				SetActorEnableCollision(false);
			    RootComponent->SetRelativeScale3D(FVector::ZeroVector);
				SetActorHiddenInGame(true);
				//mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
				//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("%f"), reducingFactorX));
			}

		}
	
	}

	//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("%d"), shrinkPlatfrom));
}

void AShrinkingPlatform::ResetValues()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);

	 shrinkPlatfrom = false;
	 timerShrinkValue = 5;
	 timerShrink = timerShrinkValue;
	 timerRespawnValue = 5;
	 timerRespawn = timerRespawnValue;

	 ResetPlatfromScale_BP();
}

// Called every frame
void AShrinkingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Shrink(DeltaTime);
}

