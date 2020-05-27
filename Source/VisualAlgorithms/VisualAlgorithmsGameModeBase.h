// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VisualAlgorithmsGameModeBase.generated.h"

class ASortingArrayBuilder;
class AVisualizationManager;
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
	AVisualizationManager* VisualizationManager;
	ADataAlgorithms* DataAlgorithms;
	ASortingAlgorithms* SortingAlgorithms;


	//Public UFUNCTIONS() functions.
public:

	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		void SetSortingArrayBuilder(ASortingArrayBuilder* InSortingArrayBuilder) { SortingArrayBuilder = InSortingArrayBuilder; }
	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		ASortingArrayBuilder* GetSortingArrayBuilder() const { return SortingArrayBuilder; }

	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		void SetVisualizationManager(AVisualizationManager* InVisualizationManager) { VisualizationManager = InVisualizationManager; }
	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		AVisualizationManager* GetVisualizationManager() const { return VisualizationManager; }

	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		void SetDataAlgorithms(ADataAlgorithms* InDataAlgorithms) { DataAlgorithms = InDataAlgorithms; }
	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		ADataAlgorithms* GetDataAlgorithms() const { return DataAlgorithms; }

	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		void SetSortingAlgorithms(ASortingAlgorithms* InSortingAlgorithms) { SortingAlgorithms = InSortingAlgorithms; }
	UFUNCTION(BlueprintCallable, Category = "OutsideReverences")
		ASortingAlgorithms* GetSortingAlgorithms() const { return SortingAlgorithms; }

};
