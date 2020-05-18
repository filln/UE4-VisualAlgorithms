// Fill out your copyright notice in the Description page of Project Settings.


#include "AlgorithmsManager.h"
#include "VisualAlgorithmsGameModeBase.h"
#include "DataAlgorithms.h"
#include "SortingArrayBuilder.h"
#include "IndexActor.h"
#include "ValueActor.h"
#include "TimerManager.h"

// Sets default values
AAlgorithmsManager::AAlgorithmsManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsRunVisualization = false;
	TimeBetweenSwaps = 1.f;
	TranslateTimerDeltaTime = 0.017f;
	CurrentSwapsCount = 0;
	MaxSwapsCount = 0;
	SpeedOfTranslate = 10.f;

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

	CurrentSwapsCount = 0;
	MaxSwapsCount = GetDataAlgorithms()->SwapStructArr.Num();
	GetWorldTimerManager().SetTimer(SwapTimer, this, &AAlgorithmsManager::SwapValueActors, TimeBetweenSwaps, true);

	
}

ADataAlgorithms* AAlgorithmsManager::GetDataAlgorithms() const
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		ADataAlgorithms* DataAlgorithms = GameMode->GetDataAlgorithms();
		if (DataAlgorithms)
		{
			return DataAlgorithms;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("VisualAlgorithms: GetDataAlgorithms(): return nullptr."));
			return nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VisualAlgorithms: GetDataAlgorithms(): return nullptr."));
		return nullptr;
	}
}

ASortingArrayBuilder* AAlgorithmsManager::GetSortingArrayBuilder() const
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		ASortingArrayBuilder* SortingArrayBuilder = GameMode->GetSortingArrayBuilder();
		if (SortingArrayBuilder)
		{
			return SortingArrayBuilder;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("VisualAlgorithms: GetSortingArrayBuilder(): return nullptr."));
			return nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VisualAlgorithms: GetSortingArrayBuilder(): return nullptr."));
		return nullptr;
	}
}

void AAlgorithmsManager::SwapValueActors()
{
	CurrentSwapsCount++;
	if (CurrentSwapsCount > MaxSwapsCount)
	{
		SetbIsRunVisualization(false);
		GetDataAlgorithms()->ClearSwapData();
		GetWorldTimerManager().ClearTimer(SwapTimer);

		return;
	}

	int32 Index1 = GetDataAlgorithms()->SwapStructArr[CurrentSwapsCount - 1].Index1;
	int32 Index2 = GetDataAlgorithms()->SwapStructArr[CurrentSwapsCount - 1].Index2;

	CurrentValueActor1 = GetSortingArrayBuilder()->ValueActorsArray[Index1];
	CurrentValueActor2 = GetSortingArrayBuilder()->ValueActorsArray[Index2];

	AIndexActor* CurrentIndexActor1 = GetSortingArrayBuilder()->IndexActorsArray[Index1];
	AIndexActor* CurrentIndexActor2 = GetSortingArrayBuilder()->IndexActorsArray[Index2];

	EndLocationCurrentValueActor1 = CurrentIndexActor2->GetActorLocation();
	EndLocationCurrentValueActor2 = CurrentIndexActor1->GetActorLocation();

	GetWorldTimerManager().PauseTimer(SwapTimer);
	GetWorldTimerManager().SetTimer(TranslateTimer, this, &AAlgorithmsManager::TranslateValueActors, TranslateTimerDeltaTime, true);

	GetSortingArrayBuilder()->ValueActorsArray.Swap(Index1, Index2);

}

void AAlgorithmsManager::TranslateValueActors()
{
	if (
		CurrentValueActor1->GetActorLocation() == EndLocationCurrentValueActor1
		&& CurrentValueActor2->GetActorLocation() == EndLocationCurrentValueActor2
		)
	{
		GetWorldTimerManager().ClearTimer(TranslateTimer);
		GetWorldTimerManager().UnPauseTimer(SwapTimer);

		return;
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

