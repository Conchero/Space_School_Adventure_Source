// Fill out your copyright notice in the Description page of Project Settings.


#include "Wind.h"

AWind::AWind()
{

}


void AWind::BeginPlay()
{
	Super::BeginPlay();

}

void AWind::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	

	TArray<AActor*> actors;
	GetOverlappingActors(OUT actors);
	for (AActor* each : actors)
	{
		TSet<UActorComponent*> comps = each->GetComponents();
		for (UActorComponent* eachComp : comps)
		{
			if (UStaticMeshComponent* smComp = Cast<UStaticMeshComponent>(eachComp))
			{
				if (smComp->IsSimulatingPhysics())
				{
					smComp->AddImpulse(WindForce);
				}
			}
		}
	}
	{
		
	}
}
