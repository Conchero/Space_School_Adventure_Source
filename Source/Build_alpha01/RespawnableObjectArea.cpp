// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnableObjectArea.h"

#include "Components/ShapeComponent.h"
#include "LD/RespawnableObject.h"

ARespawnableObjectArea::ARespawnableObjectArea()
{
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARespawnableObjectArea::OnOverlapBegin);
}

void ARespawnableObjectArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARespawnableObject* actor = Cast<ARespawnableObject>(OtherActor);
	if (actor)
	{
		actor->RespawnObject();
	}
}

void ARespawnableObjectArea::BeginPlay()
{
	Super::BeginPlay();

}
