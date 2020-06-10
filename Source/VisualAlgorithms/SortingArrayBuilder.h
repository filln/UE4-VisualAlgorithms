// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

/*
This class build array for algorithms and its visual representation.
*/

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

	//Count of the elements in the array for algorithms.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin="2", ClampMax="1000"), Category = "SortingArrayBuilder")
		int32 CountOfElements;

	//Location from wich build the visual array IndexActor and ValueActor. 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SortingArrayBuilder")
		FVector BeginLocation;

	//Step between previous actor and next actor in visual array.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SortingArrayBuilder")
		FVector DeltaLocation;

	//The array that will be sort.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SortingArrayBuilder")
		TArray<int32> SortingArray;

	//Container of references to IndexActors that spawned.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SortingArrayBuilder")
		TArray<AIndexActor*> IndexActorsArray;

	//Container of references to ValueActors that spawned.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SortingArrayBuilder")
		TArray<AValueActor*> ValueActorsArray;

	//Subclass of the IndexActors that will be spawn.
	UPROPERTY(EditDefaultsOnly, Category = "SortingArrayBuilder")
		TSubclassOf<AIndexActor> IndexActorClass;

	//Subclass of the ValueActors that will be spawn.
	UPROPERTY(EditDefaultsOnly, Category = "SortingArrayBuilder")
		TSubclassOf<AValueActor> ValueActorClass;

	//Limit of CountOfElements.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "SortingArrayBuilder")
		int32 MaxCountOfElements;

	//Public UFUNCTION functions;
public:

	//Set reference to this in the GameMode.
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void SetReferenceToThis();

	//Create and fill the array that will be sort.
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void BuildSortingArray();

	//Create visual representation of the array that will be sort. Spawn ValueActors and IndexActors.
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void BuildVisibleArray();

	//Clear arrays and destroy all actors.
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void DestroySortAndVisibleArrays();

	//Count of the elements in the array for algorithms.
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void SetCountOfElements(int32 InCountOfElements) { CountOfElements = InCountOfElements; }
	//Count of the elements in the array for algorithms.
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		int32 GetCountOfElements() const { return CountOfElements; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
