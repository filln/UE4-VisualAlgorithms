// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlgorithmsManager.generated.h"

class ADataAlgorithms;

UCLASS()
class VISUALALGORITHMS_API AAlgorithmsManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAlgorithmsManager();

	//Private variables.
private:

	bool bIsRunVisualization;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


};
