// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlgorithmsManager.generated.h"

class ADataAlgorithms;
class ASortingArrayBuilder;
class AIndexActor;
class AValueActor;

UENUM(BlueprintType, Category = "AlgorithmsManager")
enum class EAxisStateValueActor1 : uint8
{
	//
	EAS_CalculateX	UMETA(DisplayName = "CalculateX"),

	//
	EAS_CalculateY	UMETA(DisplayName = "CalculateY"),

	//
	EAS_CalculateZ	UMETA(DisplayName = "CalculateZ"),

};

UENUM(BlueprintType, Category = "AlgorithmsManager")
enum class EAxisStateValueActor2 : uint8
{
	//
	EAS_CalculateX	UMETA(DisplayName = "CalculateX"),

	//
	EAS_CalculateY	UMETA(DisplayName = "CalculateY"),

	//
	EAS_CalculateZ	UMETA(DisplayName = "CalculateZ"),

};

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
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		bool bIsArc;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float AxisXValueActor1;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float AxisYValueActor1;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float AxisZValueActor1;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float AxisXValueActor2;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float AxisYValueActor2;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		float AxisZValueActor2;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		EAxisStateValueActor1 AxisStateValueActor1;
	UPROPERTY(EditDefaultsOnly, Category = "AlgorithmsManager")
		EAxisStateValueActor2 AxisStateValueActor2;

	//Private variables.
private:

	bool bIsRunVisualization;
	FTimerHandle SwapTimer;
	FTimerHandle TranslateTimer;
	size_t CurrentSwapsCount;
	size_t MaxSwapsCount;
	AValueActor* ValueActor1;
	AValueActor* ValueActor2;
	FVector EndLocationValueActor1;
	FVector EndLocationValueActor2;
	FVector DeltaTranslationValueActor1;
	FVector DeltaTranslationValueActor2;

	float CountOfIteration;
	size_t CountOfIterationInt;
	size_t CurrentCountOfIteration;

	float DeltaDegreesValueActor1;
	float DeltaDegreesValueActor2;
	FVector AxisValueActor1;
	FVector AxisValueActor2;

	FVector VectorBetweenCenterAndValueActor1;
	FVector VectorBetweenCenterAndValueActor2;
	FVector CenterLocation;

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
	void SwapValueActorsArc();
	void TranslateValueActorsArc();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


};
