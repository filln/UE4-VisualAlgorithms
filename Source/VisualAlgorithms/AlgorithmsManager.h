// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlgorithmsManager.generated.h"

class ADataAlgorithms;
class ASortingArrayBuilder;
class AIndexActor;
class AValueActor;

UCLASS()
class VISUALALGORITHMS_API AAlgorithmsManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAlgorithmsManager();

	//Public UPROPERTY() variables.
public:

	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float TimeBetweenSwaps;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float TranslateTimerDeltaTime;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float TimeDurationOfSwap;

	//Private variables.
private:

	bool bIsRunVisualization;
	FTimerHandle SwapTimer;
	FTimerHandle TranslateTimer;
	size_t CurrentSwapsCount;
	size_t MaxSwapsCount;
	AValueActor* CurrentValueActor1;
	AValueActor* CurrentValueActor2;
	FVector EndLocationCurrentValueActor1;
	FVector EndLocationCurrentValueActor2;
	FVector DeltaTranslationValueActor1;
	FVector DeltaTranslationValueActor2;

	float CountOfIteration;
	size_t CountOfIterationInt;
	size_t CurrentCountOfIteration;
		

	//Public UFUNCTION() functions.
public:

	UFUNCTION(BlueprintCallable, Category = "AlgorithmsManager")
		void SetReferenceToThis();

	UFUNCTION(BlueprintCallable, Category = "AlgorithmsManager")
		void RunVisualization();

	UFUNCTION(BlueprintCallable, Category = "AlgorithmsManager")
		bool GetbIsRunVisualization() const { return bIsRunVisualization; }
	UFUNCTION(BlueprintCallable, Category = "AlgorithmsManager")
		void SetbIsRunVisualization(bool bInIsRunVisualization) { bIsRunVisualization = bInIsRunVisualization; }

	UFUNCTION(BlueprintCallable, Category = "AlgorithmsManager")
		ADataAlgorithms* GetDataAlgorithms() const;
	UFUNCTION(BlueprintCallable, Category = "AlgorithmsManager")
		ASortingArrayBuilder* GetSortingArrayBuilder() const;

private:

	void SwapValueActors();
	void TranslateValueActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


};
