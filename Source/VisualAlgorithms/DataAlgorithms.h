// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

/*
The class that saves and manages data of events in algorithms.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataAlgorithms.generated.h"


//This structure saves indexes of values that exchange.
USTRUCT(BlueprintType)
struct FSwapStruct
{
	GENERATED_USTRUCT_BODY()

	int32 Index1;
	int32 Index2;
};

UCLASS()
class VISUALALGORITHMS_API ADataAlgorithms : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADataAlgorithms();

	//Public UPROPERTY() variables.
public:

	//The array keeps structures FSwapStruct.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DataAlgorithms")
		TArray<FSwapStruct> SwapStructArr;

	//Public UFUNCTION() functions.

public:

	//Set reference to this in the GameMode.
	UFUNCTION(BlueprintCallable, Category = "DataAlgorithms")
		void SetReferenceToThis();

	//Save information about exchange.
	UFUNCTION(BlueprintCallable, Category = "DataAlgorithms")
		void WriteSwapData(int32 Index1, int32 Index2);

	//Clear information about all exchanges.
	UFUNCTION(BlueprintCallable, Category = "DataAlgorithms")
		void ClearSwapData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
