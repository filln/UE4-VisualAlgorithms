// Copyright 2020 Anatoli Kucharau. All Rights Reserved.


#include "SortingAlgorithms.h"
#include "VisualAlgorithmsGameModeBase.h"
#include "DataAlgorithms.h"
#include <random>

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

void ASortingAlgorithms::ShuffleArray(TArray<int32>& Arr)
{
	size_t lastIndex = Arr.Num() - 1;

	std::random_device rd;

	//	std::mt19937 generator(rd());
	std::default_random_engine generator(rd());

	for (size_t index = 0; index <= lastIndex; index++)
	{
		std::uniform_int_distribution<int> distribution(0, (int)lastIndex);
		size_t randomIndex = distribution(generator);

		if (randomIndex == index)
		{
			if (randomIndex == lastIndex)
			{
				--randomIndex;
			}
			else
			{
				++randomIndex;
			}
		}

		Arr.Swap(index, randomIndex);

		WriteSwapData(index, randomIndex);

	}

}

void ASortingAlgorithms::BubbleSort(TArray<int32>& Arr)
{

	size_t lastIndex = Arr.Num() - 1;

	bool isSwap = true;
	while (isSwap)
	{
		isSwap = false;
		for (size_t index = 0; index < lastIndex; index++)
		{
			if (Arr[index] > Arr[index + 1])
			{
				Arr.Swap(index, index + 1);
				isSwap = true;

				WriteSwapData(index, index + 1);
			}
		}
		lastIndex--;
	}

}

ADataAlgorithms* ASortingAlgorithms::GetDataAlgorithms() const
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

void ASortingAlgorithms::WriteSwapData(int32 Index1, int32 Index2)
{
	ADataAlgorithms* DataAlgorithms = GetDataAlgorithms();
	if (DataAlgorithms)
	{
		DataAlgorithms->WriteSwapData(Index1, Index2);
	}
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

