// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VisualAlgorithmsGameModeBase.generated.h"

class ASortingArrayBuilder;
class AAlgorithmsManager;
class ADataAlgorithms;
class ASortingAlgorithms;

/**
 * 
 */
UCLASS()
class VISUALALGORITHMS_API AVisualAlgorithmsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
		//Private variables.
private:

	ASortingArrayBuilder* SortingArrayBuilder;
	AAlgorithmsManager* AlgorithmsManager;
	ADataAlgorithms* DataAlgorithms;
	ASortingAlgorithms* SortingAlgorithms;


	//Public UFUNCTIONS() functions.
public:

	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		void SetSortingArrayBuilder(ASortingArrayBuilder* InSortingArrayBuilder) { SortingArrayBuilder = InSortingArrayBuilder; }
	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		ASortingArrayBuilder* GetSortingArrayBuilder() const { return SortingArrayBuilder; }

	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		void SetAlgorithmsManager(AAlgorithmsManager* InAlgorithmsManager) { AlgorithmsManager = InAlgorithmsManager; }
	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		AAlgorithmsManager* GetAlgorithmsManager() const { return AlgorithmsManager; }

	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		void SetDataAlgorithms(ADataAlgorithms* InDataAlgorithms) { DataAlgorithms = InDataAlgorithms; }
	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		ADataAlgorithms* GetDataAlgorithms() const { return DataAlgorithms; }

	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		void SetSortingAlgorithms(ASortingAlgorithms* InSortingAlgorithms) { SortingAlgorithms = InSortingAlgorithms; }
	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		ASortingAlgorithms* GetSortingAlgorithms() const { return SortingAlgorithms; }

};
