// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

/* 
This class contains algorithms (shuffle, sorting etc.) and methods that save events in these algorithms.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortingAlgorithms.generated.h"

class ADataAlgorithms;

UCLASS()
class VISUALALGORITHMS_API ASortingAlgorithms : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASortingAlgorithms();

	//Public UFUNCTION() functions.
public:

	//Set reference to this in the GameMode.
	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void SetReferenceToThis();

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void ShuffleArray(UPARAM(ref) TArray<int32>& Arr);

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void SelectSort(UPARAM(ref) TArray<int32>& Arr);

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void BubbleSort(UPARAM(ref) TArray<int32>& Arr);

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void InsertSort(UPARAM(ref) TArray<int32>& Arr);

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void ShellSort(UPARAM(ref) TArray<int32>& Arr);

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void HeapSort(UPARAM(ref) TArray<int32>& Arr);

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void QuickSort(UPARAM(ref) TArray<int32>& Arr);

	//Save data of exchange to SwapStructArr in DataAlgotithms.
	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		void WriteSwapData(int32 Index1, int32 Index2);


	//Private functions.
private:

	ADataAlgorithms* GetDataAlgorithms() const;

	//Build pyramid for HeapSort().
	void DownHeap(TArray<int32>& Arr, int32 index1, int32 index2);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
