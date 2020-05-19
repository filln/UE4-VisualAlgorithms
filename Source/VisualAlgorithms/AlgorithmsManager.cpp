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
	TimeDurationOfSwap = 1.f;

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
	GetWorldTimerManager().SetTimer(SwapTimer, this, &AAlgorithmsManager::SwapValueActors, TimeBetweenSwaps, false);


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

	float CountOfIteration = TimeDurationOfSwap / TranslateTimerDeltaTime;
	int32 CountOfInterval = Index1 - Index2;
	if (CountOfInterval < 0)
	{
		CountOfInterval *= -1;
	}
	FVector DeltaTranslation = (GetSortingArrayBuilder()->DeltaLocation / CountOfIteration) * CountOfInterval;

	if (Index1 > Index2)
	{
		DeltaTranslationValueActor1 = DeltaTranslation * -1.f;
		DeltaTranslationValueActor2 = DeltaTranslation;
	}
	if (Index2 > Index1)
	{
		DeltaTranslationValueActor1 = DeltaTranslation;
		DeltaTranslationValueActor2 = DeltaTranslation * -1.f;
	}

	UE_LOG(LogTemp, Warning, TEXT("EndLocationCurrentValueActor1 is %s."), *EndLocationCurrentValueActor1.ToString());

	GetWorldTimerManager().ClearTimer(SwapTimer);
	GetWorldTimerManager().SetTimer(TranslateTimer, this, &AAlgorithmsManager::TranslateValueActors, TranslateTimerDeltaTime, true);

	GetSortingArrayBuilder()->ValueActorsArray.Swap(Index1, Index2);

}

void AAlgorithmsManager::TranslateValueActors()
{
	FVector NextLocationCurrentValueActor1 = CurrentValueActor1->GetActorLocation() + DeltaTranslationValueActor1;
	FVector NextLocationCurrentValueActor2 = CurrentValueActor2->GetActorLocation() + DeltaTranslationValueActor2;
	UE_LOG(LogTemp, Warning, TEXT("NextLocationCurrentValueActor1 is %s."), *NextLocationCurrentValueActor1.ToString());

	if (
		NextLocationCurrentValueActor1 == EndLocationCurrentValueActor1
		|| NextLocationCurrentValueActor2 == EndLocationCurrentValueActor2
		)
	{
		CurrentValueActor1->SetActorLocation(EndLocationCurrentValueActor1);
		CurrentValueActor2->SetActorLocation(EndLocationCurrentValueActor2);

		GetWorldTimerManager().ClearTimer(TranslateTimer);
		GetWorldTimerManager().SetTimer(SwapTimer, this, &AAlgorithmsManager::SwapValueActors, TimeBetweenSwaps, true, TimeBetweenSwaps);

		return;
	}

	CurrentValueActor1->SetActorLocation(NextLocationCurrentValueActor1);
	CurrentValueActor2->SetActorLocation(NextLocationCurrentValueActor2);

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

