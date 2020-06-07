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


void ASortingAlgorithms::QuickSort(TArray<int32>& Arr)
{
	/*

	int32 MaxStack = 64;
	int32 index1, index2; // указатели, участвующие в разделении
	int32 lb, ub; // границы сортируемого в цикле фрагмента

	int32 lbstack[MaxStack], ubstack[MaxStack]; // стек запросов
	// каждый запрос задаетс€ парой значений,
	// а именно: левой(lbstack) и правой(ubstack)
	// границами промежутка
	int32 stackpos = 1; // текуща€ позици€ стека
	int32 ppos; // середина массива
	int32 pivot; // опорный элемент
	int32 temp;

	lbstack[1] = 0;
	ubstack[1] = size - 1;

	do {
		// ¬з€ть границы lb и ub текущего массива из стека.
		lb = lbstack[stackpos];
		ub = ubstack[stackpos];
		stackpos--;

		do {
			// Ўаг 1. –азделение по элементу pivot
			ppos = (lb + ub) >> 1;
			index1 = lb; index2 = ub; pivot = Arr[ppos];
			do {
				while (Arr[index1] < pivot) index1++;
				while (pivot < Arr[index2]) index2--;
				if (index1 <= index2) {
					Arr.Swap(index1, index2);
					WriteSwapData(index1, index2);
					index1++; index2--;
				}
			} while (index1 <= index2);

			// —ейчас указатель i указывает на начало правого подмассива,
			// j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
			// ¬озможен случай, когда указатель i или j выходит за границу массива

			// Ўаги 2, 3. ќтправл€ем большую часть в стек и двигаем lb,ub
			if (index1 < ppos) { // права€ часть больше
				if (index1 < ub) { // если в ней больше 1 элемента - нужно
					stackpos++; // сортировать, запрос в стек
					lbstack[stackpos] = index1;
					ubstack[stackpos] = ub;
				}
				ub = index2; // следующа€ итераци€ разделени€
				// будет работать с левой частью
			}
			else { // лева€ часть больше
				if (index2 > lb) {
					stackpos++;
					lbstack[stackpos] = lb;
					ubstack[stackpos] = index2;
				}
				lb = index1;
			}
		} while (lb < ub); // пока в меньшей части более 1 элемента
	} while (stackpos != 0); // пока есть запросы в стеке

	*/
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

