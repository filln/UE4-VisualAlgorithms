// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VisualAlgorithmsHUD.generated.h"

class ASortingAlgorithms;
class AVisualizationManager;
class ASortingArrayBuilder;
class ADataAlgorithms;

/**
 * 
 */
UCLASS()
class VISUALALGORITHMS_API AVisualAlgorithmsHUD : public AHUD
{
	GENERATED_BODY()


		//Public UFUNCTION() function.
public:

	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		ASortingAlgorithms* GetSortingAlgorithms() const;
	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		AVisualizationManager* GetVisualizationManager() const;
	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		ASortingArrayBuilder* GetSortingArrayBuilder() const;
	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		ADataAlgorithms* GetDataAlgorithms() const;
	
};
