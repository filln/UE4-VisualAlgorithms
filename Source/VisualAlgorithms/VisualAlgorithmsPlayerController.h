// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VisualAlgorithmsPlayerController.generated.h"

/**
 *
 */
UCLASS()
class VISUALALGORITHMS_API AVisualAlgorithmsPlayerController : public APlayerController
{
	GENERATED_BODY()


		//Public UFUNCTIONS() functions.
public:

	/*Set mode "Game and UI" and show cursor.*/
	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithmsPlayerController")
	void SetInputModeGameAndUI();





};
