// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

#include "DataAlgorithms.h"
#include "VisualAlgorithmsGameModeBase.h"


// Sets default values
ADataAlgorithms::ADataAlgorithms()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ADataAlgorithms::SetReferenceToThis()
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		GameMode->SetDataAlgorithms(this);
	}
}

void ADataAlgorithms::WriteSwapData(int32 Index1, int32 Index2)
{
	//Create struct and add it to array.
	FSwapStruct SwapStruct;
	SwapStruct.Index1 = Index1;
	SwapStruct.Index2 = Index2;
	SwapStructArr.Add(SwapStruct);
}

void ADataAlgorithms::ClearSwapData()
{
	SwapStructArr.Empty();
}

// Called when the game starts or when spawned
void ADataAlgorithms::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADataAlgorithms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

