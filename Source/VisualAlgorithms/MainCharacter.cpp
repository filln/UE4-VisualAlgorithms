// Copyright 2020 Anatoli Kucharau. All Rights Reserved.


#include "MainCharacter.h"
#include "SortingAlgorithms.h"
#include "VisualizationManager.h"
#include "SortingArrayBuilder.h"
#include "DataAlgorithms.h"
#include "VisualAlgorithmsGameModeBase.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

ASortingAlgorithms* AMainCharacter::GetSortingAlgorithms() const
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

AVisualizationManager* AMainCharacter::GetVisualizationManager() const
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

ASortingArrayBuilder* AMainCharacter::GetSortingArrayBuilder() const
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

ADataAlgorithms* AMainCharacter::GetDataAlgorithms() const
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

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

