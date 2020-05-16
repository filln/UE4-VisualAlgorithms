// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlgorithmsManager.generated.h"

UCLASS()
class VISUALALGORITHMS_API AAlgorithmsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlgorithmsManager();

	//Public UFUNCTION() functions.
public:

	UFUNCTION(BlueprintCallable, Category = "AlgorithmsManager")
		void SetReferenceToThis();

	UFUNCTION(BlueprintCallable, Category = "AlgorithmsManager")
		void RunVisualization();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
