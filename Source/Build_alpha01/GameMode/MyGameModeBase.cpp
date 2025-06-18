// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
//exemple de stockage de reference d'objet :
//void AMyGameModeBase::BeginPlay()
//{
//	Super::BeginPlay();
//
//	TArray<AActor*> FoundActors;
//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("colid")));
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractible::StaticClass(), FoundActors);
//
//
//	for (AActor* TActor : FoundActors)
//	{
//		m_interactibles.Add(Cast<AInteractible>(TActor));
//	}
//
//	//PrintNomberOfInteractibleLess();
//}
//void AMyGameModeBase::Tick(float DeltaSeconds)
//{
//
//	Super::Tick(DeltaSeconds);
//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("wewe")));
//
//
//	//TArray<AActor*> FoundActors;
//	////GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("colid")));
//	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractible::StaticClass(), FoundActors);
//
//
//	//for (AActor* TActor : FoundActors)
//	//{
//	//	m_interactibles.Add(Cast<AInteractible>(TActor));
//	//	////AInteractible* MyActor = Cast<AInteractible>(TActor);
//	//	//m_interactibles = Cast<AInteractible>(TActor);
//
//	//	//if (MyActor != nullptr)
//	//	//{
//	//	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Et de 1")));
//	//	//}
//	//	//	// Do what ever you need with your MyActor
//	//}
//	////	m_interactibles = Cast<AInteractible*>();
//}
//
//
//void AMyGameModeBase::PrintNomberOfInteractibleLess()
//{
//	m_interactibles.Empty();
//
//	TArray<AActor*> FoundActors;
//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("colid")));
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractible::StaticClass(), FoundActors);
//
//
//	for (AActor* TActor : FoundActors)
//	{
//		m_interactibles.Add(Cast<AInteractible>(TActor));
//	}
//
//	int32 nbInteractible = 0;
//	for (AInteractible* interactibles : m_interactibles)
//	{
//		nbInteractible++;
//	}
//
//	//Convertion de type
//	//FString nb = FString::FromInt(nbInteractible);
//
//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("nb Interactible less = %d"), nbInteractible));
//
//}

//Fin d'exemple