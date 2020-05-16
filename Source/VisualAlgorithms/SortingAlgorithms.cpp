// Fill out your copyright notice in the Description page of Project Settings.


#include "SortingAlgorithms.h"
#include "VisualAlgorithmsGameModeBase.h"

// Sets default values
ASortingAlgorithms::ASortingAlgorithms()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}



void ASortingAlgorithms::SetReferenceToThis()
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		GameMode->SetSortingAlgorithms(this);
	}
}

void ASortingAlgorithms::BubbleSort(TArray<uint8>& Arr)
{

}

// Called when the game starts or when spawned
void ASortingAlgorithms::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASortingAlgorithms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

