// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualAlgorithmsHUD.h"
#include "SortingAlgorithms.h"
#include "VisualizationManager.h"
#include "SortingArrayBuilder.h"
#include "DataAlgorithms.h"
#include "VisualAlgorithmsGameModeBase.h"

ASortingAlgorithms* AVisualAlgorithmsHUD::GetSortingAlgorithms() const
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		return GameMode->GetSortingAlgorithms();
	}
	else
	{
		return nullptr;
	}
}

AVisualizationManager* AVisualAlgorithmsHUD::GetVisualizationManager() const
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		return GameMode->GetVisualizationManager();
	}
	else
	{
		return nullptr;
	}
}

ASortingArrayBuilder* AVisualAlgorithmsHUD::GetSortingArrayBuilder() const
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		return GameMode->GetSortingArrayBuilder();
	}
	else
	{
		return nullptr;
	}
}

ADataAlgorithms* AVisualAlgorithmsHUD::GetDataAlgorithms() const
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		return GameMode->GetDataAlgorithms();
	}
	else
	{
		return nullptr;
	}
}
