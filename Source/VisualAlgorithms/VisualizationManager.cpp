// Copyright 2020 Anatoli Kucharau. All Rights Reserved.


#include "VisualizationManager.h"
#include "VisualAlgorithmsGameModeBase.h"
#include "DataAlgorithms.h"
#include "SortingArrayBuilder.h"
#include "IndexActor.h"
#include "ValueActor.h"
#include "TimerManager.h"

// Sets default values
AVisualizationManager::AVisualizationManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsRunVisualization = false;
	TimeBetweenSwaps = 1.f;
	TranslateTimerDeltaTime = 0.017f;
	CurrentSwapsCount = 0;
	MaxSwapsCount = 0;
	TimeDurationOfSwap = 1.f;
	bIsArc = true;
	AxisValueActor1 = FVector(-30.0f, -1.0f, -1.0f);
	AxisValueActor2 = FVector(-30.0f, 1.0f, 1.0f);
	AxisStateValueActor1 = EAxisStateValueActor1::EAS_CalculateZ;
	AxisStateValueActor2 = EAxisStateValueActor2::EAS_CalculateZ;

}

void AVisualizationManager::SetReferenceToThis()
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		GameMode->SetVisualizationManager(this);
	}
}

void AVisualizationManager::RunVisualization()
{
	CurrentSwapsCount = 0;
	MaxSwapsCount = GetDataAlgorithms()->SwapStructArr.Num();

	if (MaxSwapsCount == 0)
	{
		SetbIsRunVisualization(false);
		return;
	}

	SetbIsRunVisualization(true);

	OnIsRunVisualization.Broadcast(GetbIsRunVisualization());
	SwapValueActors();

}

void AVisualizationManager::FinishImmediately()
{
	if (!GetbIsRunVisualization())
	{
		return;
	}

	GetWorldTimerManager().ClearTimer(TranslateTimer);
	GetWorldTimerManager().ClearTimer(SwapTimer);

	//Translate the actors to its indexes.
	for (CurrentSwapsCount; CurrentSwapsCount < MaxSwapsCount; CurrentSwapsCount++)
	{
		Index1 = GetDataAlgorithms()->SwapStructArr[CurrentSwapsCount].Index1;
		Index2 = GetDataAlgorithms()->SwapStructArr[CurrentSwapsCount].Index2;

		ValueActor1 = GetSortingArrayBuilder()->ValueActorsArray[Index1];
		ValueActor2 = GetSortingArrayBuilder()->ValueActorsArray[Index2];

		AIndexActor* IndexActor1 = GetSortingArrayBuilder()->IndexActorsArray[Index1];
		AIndexActor* IndexActor2 = GetSortingArrayBuilder()->IndexActorsArray[Index2];

		EndLocationValueActor1 = IndexActor2->GetActorLocation();
		EndLocationValueActor2 = IndexActor1->GetActorLocation();

		ValueActor1->SetActorLocation(EndLocationValueActor1);
		ValueActor2->SetActorLocation(EndLocationValueActor2);

		GetSortingArrayBuilder()->ValueActorsArray.Swap(Index1, Index2);

		//UE_LOG(LogTemp, Warning, TEXT("CurrentSwapsCount is %d."), CurrentSwapsCount);
	}

	SetbIsRunVisualization(false);
	GetDataAlgorithms()->ClearSwapData();
	CurrentSwapsCount = 0;
	OnIsRunVisualization.Broadcast(GetbIsRunVisualization());
}

ADataAlgorithms* AVisualizationManager::GetDataAlgorithms() const
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

ASortingArrayBuilder* AVisualizationManager::GetSortingArrayBuilder() const
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

void AVisualizationManager::SwapValueActors()
{

	Index1 = GetDataAlgorithms()->SwapStructArr[CurrentSwapsCount].Index1;
	Index2 = GetDataAlgorithms()->SwapStructArr[CurrentSwapsCount].Index2;

	ValueActor1 = GetSortingArrayBuilder()->ValueActorsArray[Index1];
	ValueActor2 = GetSortingArrayBuilder()->ValueActorsArray[Index2];

	AIndexActor* IndexActor1 = GetSortingArrayBuilder()->IndexActorsArray[Index1];
	AIndexActor* IndexActor2 = GetSortingArrayBuilder()->IndexActorsArray[Index2];

	EndLocationValueActor1 = IndexActor2->GetActorLocation();
	EndLocationValueActor2 = IndexActor1->GetActorLocation();

	//Start point of actor translate.
	FVector StartLocationValueActor1 = ValueActor1->GetActorLocation();
	//Start point of actor translate.
	FVector StartLocationValueActor2 = ValueActor2->GetActorLocation();

	//CountOfIteration corresponds to TimeDurationOfSwap and TranslateTimerDeltaTime.
	CountOfIteration = TimeDurationOfSwap / TranslateTimerDeltaTime;
	CountOfIterationInt = static_cast<size_t>(CountOfIteration);
	CurrentCountOfIteration = 0;


	int32 CountOfInterval = Index1 - Index2;

	//Set CountOfInterval positive.
	if (CountOfInterval < 0)
	{
		CountOfInterval *= -1;
	}

	//The vector that actors translate every TranslateTimer tick.
	FVector DeltaTranslation = (GetSortingArrayBuilder()->DeltaLocation / CountOfIteration) * CountOfInterval;

	//The angle that actors translate every TranslateTimer tick.
	float DeltaDegrees = 180 / CountOfIteration;

	//The vector between ValueActor1 and ValueActor2.
	FVector VectorBetweenValueActors = StartLocationValueActor2 - StartLocationValueActor1;
	VectorBetweenCenterAndValueActor2 = VectorBetweenValueActors - VectorBetweenValueActors / 2;
	VectorBetweenCenterAndValueActor1 = -VectorBetweenCenterAndValueActor2;
	CenterLocation = StartLocationValueActor2 - VectorBetweenCenterAndValueActor2;

	//This block change direction of translation of actors.
	if (Index1 > Index2)
	{
		DeltaTranslationValueActor1 = DeltaTranslation * -1.f;
		DeltaTranslationValueActor2 = DeltaTranslation;

		DeltaDegreesValueActor1 = DeltaDegrees * -1.f;
		DeltaDegreesValueActor2 = DeltaDegrees;
	}
	if (Index2 > Index1)
	{
		DeltaTranslationValueActor1 = DeltaTranslation;
		DeltaTranslationValueActor2 = DeltaTranslation * -1.f;

		DeltaDegreesValueActor1 = DeltaDegrees;
		DeltaDegreesValueActor2 = DeltaDegrees * -1.f;
	}

	/*
	This block calculate Axis around that actors rotation depend to vector between CenterLocation and current actor 
	and depend to defenition of two cordinates of this Axis.
	Ax*Bx + Ay*By + Az*Bz = 0 for perpendicular vectors.
	*/
	switch (AxisStateValueActor1)
	{
	case EAxisStateValueActor1::EAS_CalculateX:
		AxisValueActor1.X = -(VectorBetweenCenterAndValueActor1.Y * AxisValueActor1.Y + VectorBetweenCenterAndValueActor1.Z * AxisValueActor1.Z) / VectorBetweenCenterAndValueActor1.X;
		break;
	case EAxisStateValueActor1::EAS_CalculateY:
		AxisValueActor1.Y = -(VectorBetweenCenterAndValueActor1.X * AxisValueActor1.X + VectorBetweenCenterAndValueActor1.Z * AxisValueActor1.Z) / VectorBetweenCenterAndValueActor1.Y;
		break;
	case EAxisStateValueActor1::EAS_CalculateZ:
		AxisValueActor1.Z = -(VectorBetweenCenterAndValueActor1.X * AxisValueActor1.X + VectorBetweenCenterAndValueActor1.Y * AxisValueActor1.Y) / VectorBetweenCenterAndValueActor1.Z;
		break;
	default:
		break;
	}
	switch (AxisStateValueActor2)
	{
	case EAxisStateValueActor2::EAS_CalculateX:
		AxisValueActor2.X = -(VectorBetweenCenterAndValueActor2.Y * AxisValueActor2.Y + VectorBetweenCenterAndValueActor2.Z * AxisValueActor2.Z) / VectorBetweenCenterAndValueActor2.X;
		break;
	case EAxisStateValueActor2::EAS_CalculateY:
		AxisValueActor2.Y = -(VectorBetweenCenterAndValueActor2.X * AxisValueActor2.X + VectorBetweenCenterAndValueActor2.Z * AxisValueActor2.Z) / VectorBetweenCenterAndValueActor2.Y;
		break;
	case EAxisStateValueActor2::EAS_CalculateZ:
		AxisValueActor2.Z = -(VectorBetweenCenterAndValueActor2.X * AxisValueActor2.X + VectorBetweenCenterAndValueActor2.Y * AxisValueActor2.Y) / VectorBetweenCenterAndValueActor2.Z;
		break;
	default:
		break;
	}

	AxisValueActor1.Normalize();
	AxisValueActor2.Normalize();

	//UE_LOG(LogTemp, Warning, TEXT("EndLocationCurrentValueActor1 is %s."), *EndLocationCurrentValueActor1.ToString());

	//Go translate actors!
	GetWorldTimerManager().SetTimer(TranslateTimer, this, &AVisualizationManager::TranslateValueActors, TranslateTimerDeltaTime, true);


}

void AVisualizationManager::TranslateValueActors()
{
	CurrentCountOfIteration++;

	//If used all iteration than correct finish point and start exchange next actors.
	//Stop exchange if all exchanges was done.
	if (CurrentCountOfIteration == CountOfIterationInt)
	{
		ValueActor1->SetActorLocation(EndLocationValueActor1);
		ValueActor2->SetActorLocation(EndLocationValueActor2);
		GetSortingArrayBuilder()->ValueActorsArray.Swap(Index1, Index2);

		GetWorldTimerManager().ClearTimer(TranslateTimer);

		CurrentSwapsCount++;
		//Stop exchange if all exchanges was done.
		if (CurrentSwapsCount >= MaxSwapsCount)
		{
			SetbIsRunVisualization(false);
			GetDataAlgorithms()->ClearSwapData();
			CurrentSwapsCount = 0;

			OnIsRunVisualization.Broadcast(GetbIsRunVisualization());

			return;
		}

		GetWorldTimerManager().SetTimer(SwapTimer, this, &AVisualizationManager::SwapValueActors, TimeBetweenSwaps, false, TimeBetweenSwaps);

		return;
	}

	FVector NextLocationValueActor1;
	FVector NextLocationValueActor2;

	//If true than calculate arc. Else calculate line.
	if (bIsArc)
	{
		VectorBetweenCenterAndValueActor1 = VectorBetweenCenterAndValueActor1.RotateAngleAxis(DeltaDegreesValueActor1, AxisValueActor1);
		VectorBetweenCenterAndValueActor2 = VectorBetweenCenterAndValueActor2.RotateAngleAxis(DeltaDegreesValueActor2, AxisValueActor2);
		NextLocationValueActor1 = CenterLocation + VectorBetweenCenterAndValueActor1;
		NextLocationValueActor2 = CenterLocation + VectorBetweenCenterAndValueActor2;
	}
	else
	{
		NextLocationValueActor1 = ValueActor1->GetActorLocation() + DeltaTranslationValueActor1;
		NextLocationValueActor2 = ValueActor2->GetActorLocation() + DeltaTranslationValueActor2;
	}

	ValueActor1->SetActorLocation(NextLocationValueActor1);
	ValueActor2->SetActorLocation(NextLocationValueActor2);

}

// Called when the game starts or when spawned
void AVisualizationManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVisualizationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

