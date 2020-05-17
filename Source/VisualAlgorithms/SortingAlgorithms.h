// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void SetReferenceToThis();

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void ShuffleArray(UPARAM(ref) TArray<int32>& Arr);

	UFUNCTION(BlueprintCallable, Category = "SortingAlgorithms")
		void BubbleSort(UPARAM(ref) TArray<int32>& Arr);

	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		void WriteSwapData(int32 Index1, int32 Index2);


	//Private functions.
private:

	ADataAlgorithms* GetDataAlgorithms() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
