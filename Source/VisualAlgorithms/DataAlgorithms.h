// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataAlgorithms.generated.h"


USTRUCT(BlueprintType)
struct FSwapStruct
{
	GENERATED_USTRUCT_BODY()

	uint8 Index1;
	uint8 Index2;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DataAlgorithms")
		TArray<FSwapStruct> SwapStructArr;

	//Public UFUNCTION() functions.

public:

	UFUNCTION(BlueprintCallable, Category = "DataAlgorithms")
		void SetReferenceToThis();

	UFUNCTION(BlueprintCallable, Category = "DataAlgorithms")
		void WriteSwapData(uint8 Index1, uint8 Index2);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
