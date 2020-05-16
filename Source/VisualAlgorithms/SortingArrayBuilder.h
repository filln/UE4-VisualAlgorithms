// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortingArrayBuilder.generated.h"

class AIndexActor;
class AValueActor;

UCLASS()
class VISUALALGORITHMS_API ASortingArrayBuilder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASortingArrayBuilder();

	//Public UPROPERTY variables
public:

	UPROPERTY(EditAnywhere, Category = "SortingArrayBuilder")
		uint8 CountOfElements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SortingArrayBuilder")
		TArray<uint8> SortingArray;

	//Public UFUNCTION functions;
public:

	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void SetReferenceToThis();

	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void BuildSortingArray();

	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void BuildIndexActors();

	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void BuildValueActors();
	
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void SetCountOfElements(uint8 InCountOfElements) { CountOfElements = InCountOfElements; }
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		uint8 GetCountOfElements() const { return CountOfElements; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
