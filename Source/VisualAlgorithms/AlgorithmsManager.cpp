// Fill out your copyright notice in the Description page of Project Settings.


#include "AlgorithmsManager.h"
#include "VisualAlgorithmsGameModeBase.h"
#include "DataAlgorithms.h"

// Sets default values
AAlgorithmsManager::AAlgorithmsManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsRunVisualization = false;

}

void AAlgorithmsManager::SetReferenceToThis()
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		GameMode->SetAlgorithmsManager(this);
	}
}

void AAlgorithmsManager::RunVisualization()
{
	SetbIsRunVisualization(true);



	ADataAlgorithms* DataAlgorithms = GetDataAlgorithms();
	if (DataAlgorithms)
	{
		DataAlgorithms->ClearSwapData();
	}
	SetbIsRunVisualization(false);
	
}

ADataAlgorithms* AAlgorithmsManager::GetDataAlgorithms() const
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		return GameMode->GetDataAlgorithms();
	}
	else
	{
		return nullptr;
	}
}

// Called when the game starts or when spawned
void AAlgorithmsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAlgorithmsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

