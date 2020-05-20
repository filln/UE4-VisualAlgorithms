// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

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

	UPROPERTY(EditDefaultsOnly, meta=(ClampMin="0"), Category = "SortingArrayBuilder")
		int32 CountOfElements;
	UPROPERTY(EditDefaultsOnly, Category = "SortingArrayBuilder")
		FVector BeginLocation;
	UPROPERTY(EditDefaultsOnly, Category = "SortingArrayBuilder")
		FVector DeltaLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SortingArrayBuilder")
		TArray<int32> SortingArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SortingArrayBuilder")
		TArray<AIndexActor*> IndexActorsArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SortingArrayBuilder")
		TArray<AValueActor*> ValueActorsArray;

	UPROPERTY(EditDefaultsOnly, Category = "SortingArrayBuilder")
		TSubclassOf<AIndexActor> IndexActorClass;
	UPROPERTY(EditDefaultsOnly, Category = "SortingArrayBuilder")
		TSubclassOf<AValueActor> ValueActorClass;

	//Public UFUNCTION functions;
public:

	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void SetReferenceToThis();

	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void BuildSortingArray();

	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void BuildVisibleArray();

	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		void SetCountOfElements(int32 InCountOfElements) { CountOfElements = InCountOfElements; }
	UFUNCTION(BlueprintCallable, Category = "SortingArrayBuilder")
		int32 GetCountOfElements() const { return CountOfElements; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
