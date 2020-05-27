// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualAlgorithmsPlayerController.h"

void AVisualAlgorithmsPlayerController::SetInputModeGameAndUI()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}
