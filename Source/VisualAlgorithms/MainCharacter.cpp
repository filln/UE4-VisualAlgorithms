// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "SortingAlgorithms.h"
#include "AlgorithmsManager.h"
#include "SortingArrayBuilder.h"
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

AAlgorithmsManager* AMainCharacter::GetAlgorithmsManager() const
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		return GameMode->GetAlgorithmsManager();
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

