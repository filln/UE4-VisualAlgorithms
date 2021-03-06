// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

/*
The class that moves actors using data from SortingArrayBuilder and DataAlgorithms classes
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VisualizationManager.generated.h"

class ADataAlgorithms;
class ASortingArrayBuilder;
class AIndexActor;
class AValueActor;


//The delegate call when start or stop visualization in AVisualizationManager::RunVisualization(), AVisualizationManager::FinishImmediately() and AVisualizationManager::TranslateValueActors().
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsRunVisualization, bool, bIsRunVisualization);


/*
To select a vector coordinate that will be calculated. This vector is normal for the actor rotation vector.
I.e. it is the axis of the vector of rotation of the actor.
*/
UENUM(BlueprintType, Category = "VisualizationManager")
enum class EAxisStateValueActor1 : uint8
{
	//
	EAS_CalculateX	UMETA(DisplayName = "CalculateX"),

	//
	EAS_CalculateY	UMETA(DisplayName = "CalculateY"),

	//
	EAS_CalculateZ	UMETA(DisplayName = "CalculateZ"),

};

/*
To select a vector coordinate that will be calculated. This vector is normal for the actor rotation vector.
I.e. it is the axis of the vector of rotation of the actor.
*/
UENUM(BlueprintType, Category = "VisualizationManager")
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
class VISUALALGORITHMS_API AVisualizationManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVisualizationManager();

	//Public UPROPERTY() variables.
public:

	//The delegate call when start or stop visualization in AVisualizationManager::RunVisualization(), AVisualizationManager::FinishImmediately() and AVisualizationManager::TranslateValueActors().
	UPROPERTY(BlueprintAssignable, Category = "VisualizationManager")
		FOnIsRunVisualization OnIsRunVisualization;

	//The time between actors exchanges. SwapTimer timer activation period.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VisualizationManager")
		float TimeBetweenSwaps;

	//The time between little translates actors. TranslateTimer timer activation period.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VisualizationManager")
		float TranslateTimerDeltaTime;

	//The duration of the movement of actors during the exchange.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VisualizationManager")
		float TimeDurationOfSwap;

	//If true than the actors translate arc. If false than straight line.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VisualizationManager")
		bool bIsArc;

	/*
	To select a vector coordinate. This vector is normal for the actor rotation vector.
	I.e. it is the axis of the vector of rotation of the actor.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VisualizationManager")
		FVector AxisValueActor1;

	/*
	To select a vector coordinate. This vector is normal for the actor rotation vector.
	I.e. it is the axis of the vector of rotation of the actor.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VisualizationManager")
		FVector AxisValueActor2;

	/*
	To select a vector coordinate that will be calculated. This vector is normal for the actor rotation vector.
	I.e. it is the axis of the vector of rotation of the actor.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VisualizationManager")
		EAxisStateValueActor1 AxisStateValueActor1;

	/*
	To select a vector coordinate that will be calculated. This vector is normal for the actor rotation vector.
	I.e. it is the axis of the vector of rotation of the actor.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VisualizationManager")
		EAxisStateValueActor2 AxisStateValueActor2;

	//Private variables.
private:

	//State of visualization. If true than actors moving. Use for lock repeat command of visualization yet occur visualization.
	bool bIsRunVisualization;

	//Timer that repeats swap of actors. Run SwapValueActors() every tick.
	FTimerHandle SwapTimer;

	//Timer that translate actors. Run TranslateValueActors() every tick.
	FTimerHandle TranslateTimer;

	//Current count of exchange of actors.
	size_t CurrentSwapsCount;

	//Maximal count of exchange of actors.
	size_t MaxSwapsCount;

	//First index from the struct from the SwapStructArr. The struct contains indexes of actors that will be swap. 
	int32 Index1;

	//Second index from the struct from the SwapStructArr. The struct contains indexes of actors that will be swap.
	int32 Index2;

	//Actor that will be move.
	AValueActor* ValueActor1;

	//Actor that will be move.
	AValueActor* ValueActor2;

	//Finish point of actor translate.
	FVector EndLocationValueActor1;

	//Finish point of actor translate.
	FVector EndLocationValueActor2;

	//The vector that actor translate every TranslateTimer tick.
	FVector DeltaTranslationValueActor1;

	//The vector that actor translate every TranslateTimer tick.
	FVector DeltaTranslationValueActor2;

	//Count of iteration of TranslateTimer.
	float CountOfIteration;

	//Maximal count of iteration of TranslateTimer in integer.
	size_t CountOfIterationInt;

	//Current count of iteration of TranslateTimer in current tick in integer.
	size_t CurrentCountOfIteration;

	//The angle that actor translate every TranslateTimer tick.
	float DeltaDegreesValueActor1;

	//The angle that actor translate every TranslateTimer tick.
	float DeltaDegreesValueActor2;

	//The vector between point that between two actors and this actor.
	FVector VectorBetweenCenterAndValueActor1;

	//The vector between point that between two actors and this actor.
	FVector VectorBetweenCenterAndValueActor2;

	//The location of the point between two actors.
	FVector CenterLocation;

	//Public UFUNCTION() functions.
public:

	//Set reference to this in the GameMode.
	UFUNCTION(BlueprintCallable, Category = "VisualizationManager")
		void SetReferenceToThis();

	//Run visualization of the algorithm that was done.
	UFUNCTION(BlueprintCallable, Category = "VisualizationManager")
		void RunVisualization();

	//Finish  the visualization immediately.
	UFUNCTION(BlueprintCallable, Category = "VisualizationManager")
		void FinishImmediately();

	//State of visualization. If true than actors moving. Use for lock repeat command of visualization yet occur visualization.
	UFUNCTION(BlueprintCallable, Category = "VisualizationManager")
		bool GetbIsRunVisualization() const { return bIsRunVisualization; }
	//State of visualization. If true than actors moving. Use for lock repeat command of visualization yet occur visualization.
	UFUNCTION(BlueprintCallable, Category = "VisualizationManager")
		void SetbIsRunVisualization(bool bInIsRunVisualization) { bIsRunVisualization = bInIsRunVisualization; }

	//Get reference to the DataAlgorithms from the GameMode.
	UFUNCTION(BlueprintCallable, Category = "VisualizationManager")
		ADataAlgorithms* GetDataAlgorithms() const;

	//Get reference to the SortingArrayBuilder from the GameMode.
	UFUNCTION(BlueprintCallable, Category = "VisualizationManager")
		ASortingArrayBuilder* GetSortingArrayBuilder() const;

private:

	//Swap the actors and run TranslateTimer.
	void SwapValueActors();

	//Translate the actors and run SwapTimer at the end.
	void TranslateValueActors();

	//Check CurrentSwapsCount, if it is maximal value than stop swaping.
	bool CheckSwapsCount();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


};
