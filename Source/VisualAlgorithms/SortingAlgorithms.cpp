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
	int32 lastIndex = Arr.Num() - 1;

	std::random_device rd;

	//	std::mt19937 generator(rd());
	std::default_random_engine generator(rd());

	for (int32 index = 0; index <= lastIndex; index++)
	{
		std::uniform_int_distribution<int> distribution(0, (int)lastIndex);
		int32 randomIndex = distribution(generator);

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

void ASortingAlgorithms::SelectSort(TArray<int32>& Arr)
{

	int32 lastIndex = Arr.Num() - 1;
	int32 MinValue;
	for (int32 index1 = 0; index1 < lastIndex; index1++)
	{
		int32 IndexMinValue = index1;
		MinValue = Arr[index1];
		for (int32 index2 = index1 + 1; index2 <= lastIndex; index2++)
		{
			if (Arr[index2] < MinValue)
			{
				IndexMinValue = index2;
				MinValue = Arr[index2];
			}
		}
		Arr.Swap(IndexMinValue, index1);
		WriteSwapData(IndexMinValue, index1);
	}
}

void ASortingAlgorithms::BubbleSort(TArray<int32>& Arr)
{

	int32 lastIndex = Arr.Num() - 1;

	bool isSwap = true;
	while (isSwap)
	{
		isSwap = false;
		for (int32 index = 0; index < lastIndex; index++)
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

void ASortingAlgorithms::InsertSort(TArray<int32>& Arr)
{
	int32 lastIndex = Arr.Num() - 1;

	for (int32 index1 = 1, index2; index1 <= lastIndex; index1++)
	{
		for (index2 = index1; index2 > 0 && Arr[index2 - 1] > Arr[index2]; index2--)
		{
			Arr.Swap(index2 - 1, index2);
			WriteSwapData(index2 - 1, index2);
		}
	}
}

void ASortingAlgorithms::ShellSort(TArray<int32>& Arr)
{
	int32
		size = Arr.Num(),
		step,
		index1,
		index2;

	for (step = size / 2; step > 0; step /= 2)
	{
		for (index1 = step; index1 < size; index1++)
		{
			for (index2 = index1 - step; (index2 >= 0) && (Arr[index2] > Arr[index2 + step]); index2 -= step)
			{
				Arr.Swap(index2, index2 + step);
				WriteSwapData(index2, index2 + step);
			}
		}
	}
}

void ASortingAlgorithms::DownHeap(TArray<int32>& Arr, int32 index1, int32 index2)
{
	int32
		new_elem = Arr[index1],
		child;

	while (index1 <= index2 / 2)
	{
		child = 2 * index1;

		if (child < index2 && Arr[child] < Arr[child + 1])
		{
			child++;
		}

		if (new_elem >= Arr[child])
		{
			break;
		}

		Arr.Swap(child, index1);

		WriteSwapData(child, index1);

		index1 = child;
	}
}

void ASortingAlgorithms::HeapSort(TArray<int32>& Arr)
{
	int32
		size = Arr.Num(),
		index;

	for (index = size / 2 - 1; index >= 0; index--)
	{
		DownHeap(Arr, index, size - 1);
	}

	for (index = size - 1; index > 0; index--)
	{
		Arr.Swap(0, index);

		WriteSwapData(0, index);

		DownHeap(Arr, 0, index - 1);
	}
}


void ASortingAlgorithms::QuickSortIteration(TArray<int32>& Arr)
{	
	int32
		index1, index2,
		leftIndex, rightIndex,
		middleIndex;

	int32 stackPos = 1; 
	int32 Middle; 

	int32 LIstack[MaxStack], RIstack[MaxStack]; 
	
	LIstack[1] = 0;
	RIstack[1] = Arr.Num() - 1;

	do {
		leftIndex = LIstack[stackPos];
		rightIndex = RIstack[stackPos];
		stackPos--;

		do {
			middleIndex = (leftIndex + rightIndex) >> 1;
			index1 = leftIndex; index2 = rightIndex; Middle = Arr[middleIndex];
			do {
				while (Arr[index1] < Middle) index1++;
				while (Middle < Arr[index2]) index2--;
				if (index1 <= index2) {
					Arr.Swap(index1, index2);
					WriteSwapData(index1, index2);
					index1++; index2--;
				}
			} while (index1 <= index2);

			if (index1 < middleIndex) { 
				if (index1 < rightIndex) { 
					stackPos++; 
					LIstack[stackPos] = index1;
					RIstack[stackPos] = rightIndex;
				}
				rightIndex = index2; 
			}
			else {
				if (index2 > leftIndex) {
					stackPos++;
					LIstack[stackPos] = leftIndex;
					RIstack[stackPos] = index2;
				}
				leftIndex = index1;
			}
		} while (leftIndex < rightIndex); 
	} while (stackPos != 0); 	
}

void ASortingAlgorithms::QuickSortRecursion(TArray<int32>& Arr)
{
	int32 lastIndex = Arr.Num() - 1;
	_QuickSortRecursion(Arr, 0, lastIndex);
}

void ASortingAlgorithms::_QuickSortRecursion(TArray<int32>& Arr, int32 firstIndex, int32 lastIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("lastIndex is %d."), lastIndex);

	int32
		index1 = firstIndex,
		index2 = lastIndex;

	int32 Middle = Arr[(firstIndex + lastIndex) / 2];

	do {
		while (Arr[index1] < Middle) index1++;
		while (Arr[index2] > Middle) index2--;

		if (index1 <= index2) {
			Arr.Swap(index1, index2);
			WriteSwapData(index1, index2);

			index1++; index2--;
		}
	} while (index1 <= index2);

	if (index2 > 0) _QuickSortRecursion(Arr, firstIndex, index2);
	if (lastIndex > index1) _QuickSortRecursion(Arr, index1, lastIndex);
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

