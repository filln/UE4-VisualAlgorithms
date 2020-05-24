// Copyright 2020 Anatoli Kucharau. All Rights Reserved.


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
	bIsArc = true;
	AxisXValueActor1 = -30.0f;
	AxisYValueActor1 = -1.0f;
	AxisZValueActor1 = -1.0f;
	AxisXValueActor2 = -30.0f;
	AxisYValueActor2 = 1.0f;
	AxisZValueActor2 = 1.0f;
	AxisStateValueActor1 = EAxisStateValueActor1::EAS_CalculateZ;
	AxisStateValueActor2 = EAxisStateValueActor2::EAS_CalculateZ;

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

	SwapValueActors();

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

	//Stop exchange if all exchanges was done.
	if (CurrentSwapsCount > MaxSwapsCount)
	{
		SetbIsRunVisualization(false);
		GetDataAlgorithms()->ClearSwapData();
		GetWorldTimerManager().ClearTimer(SwapTimer);

		return;
	}

	int32 Index1 = GetDataAlgorithms()->SwapStructArr[CurrentSwapsCount - 1].Index1;
	int32 Index2 = GetDataAlgorithms()->SwapStructArr[CurrentSwapsCount - 1].Index2;

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
		AxisValueActor1.Y = AxisYValueActor1;
		AxisValueActor1.Z = AxisZValueActor1;
		break;
	case EAxisStateValueActor1::EAS_CalculateY:
		AxisValueActor1.X = AxisXValueActor1;
		AxisValueActor1.Y = -(VectorBetweenCenterAndValueActor1.X * AxisValueActor1.X + VectorBetweenCenterAndValueActor1.Z * AxisValueActor1.Z) / VectorBetweenCenterAndValueActor1.Y;
		AxisValueActor1.Z = AxisZValueActor1;
		break;
	case EAxisStateValueActor1::EAS_CalculateZ:
		AxisValueActor1.X = AxisXValueActor1;
		AxisValueActor1.Y = AxisYValueActor1;
		AxisValueActor1.Z = -(VectorBetweenCenterAndValueActor1.X * AxisValueActor1.X + VectorBetweenCenterAndValueActor1.Y * AxisValueActor1.Y) / VectorBetweenCenterAndValueActor1.Z;
		break;
	default:
		break;
	}
	switch (AxisStateValueActor2)
	{
	case EAxisStateValueActor2::EAS_CalculateX:
		AxisValueActor2.X = -(VectorBetweenCenterAndValueActor2.Y * AxisValueActor2.Y + VectorBetweenCenterAndValueActor2.Z * AxisValueActor2.Z) / VectorBetweenCenterAndValueActor2.X;
		AxisValueActor2.Y = AxisYValueActor2;
		AxisValueActor2.Z = AxisZValueActor2;
		break;
	case EAxisStateValueActor2::EAS_CalculateY:
		AxisValueActor2.X = AxisXValueActor2;
		AxisValueActor2.Y = -(VectorBetweenCenterAndValueActor2.X * AxisValueActor2.X + VectorBetweenCenterAndValueActor2.Z * AxisValueActor2.Z) / VectorBetweenCenterAndValueActor2.Y;
		AxisValueActor2.Z = AxisZValueActor2;
		break;
	case EAxisStateValueActor2::EAS_CalculateZ:
		AxisValueActor2.X = AxisXValueActor2;
		AxisValueActor2.Y = AxisYValueActor2;
		AxisValueActor2.Z = -(VectorBetweenCenterAndValueActor2.X * AxisValueActor2.X + VectorBetweenCenterAndValueActor2.Y * AxisValueActor2.Y) / VectorBetweenCenterAndValueActor2.Z;
		break;
	default:
		break;
	}

	AxisValueActor1.Normalize();
	AxisValueActor2.Normalize();

	//UE_LOG(LogTemp, Warning, TEXT("EndLocationCurrentValueActor1 is %s."), *EndLocationCurrentValueActor1.ToString());

	GetSortingArrayBuilder()->ValueActorsArray.Swap(Index1, Index2);

	//Go translate actors!
	GetWorldTimerManager().SetTimer(TranslateTimer, this, &AAlgorithmsManager::TranslateValueActors, TranslateTimerDeltaTime, true);


}

void AAlgorithmsManager::TranslateValueActors()
{
	CurrentCountOfIteration++;

	//If used all iteration than correct finish point and start exchange next actors.
	if (CurrentCountOfIteration == CountOfIterationInt)
	{
		ValueActor1->SetActorLocation(EndLocationValueActor1);
		ValueActor2->SetActorLocation(EndLocationValueActor2);

		GetWorldTimerManager().ClearTimer(TranslateTimer);
		GetWorldTimerManager().SetTimer(SwapTimer, this, &AAlgorithmsManager::SwapValueActors, TimeBetweenSwaps, false, TimeBetweenSwaps);

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
void AAlgorithmsManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAlgorithmsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

