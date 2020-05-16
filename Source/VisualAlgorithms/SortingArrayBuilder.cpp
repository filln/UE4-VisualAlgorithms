// Fill out your copyright notice in the Description page of Project Settings.


#include "SortingArrayBuilder.h"
#include "VisualAlgorithmsGameModeBase.h"
#include "IndexActor.h"
#include "ValueActor.h"

// Sets default values
ASortingArrayBuilder::ASortingArrayBuilder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountOfElements = 10;

}

void ASortingArrayBuilder::BuildSortingArray()
{

}

void ASortingArrayBuilder::BuildIndexActors()
{

}

void ASortingArrayBuilder::BuildValueActors()
{

}

void ASortingArrayBuilder::SetReferenceToThis()
{
	AVisualAlgorithmsGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AVisualAlgorithmsGameModeBase>();
	if (GameMode)
	{
		GameMode->SetSortingArrayBuilder(this);
	}
}


// Called when the game starts or when spawned
void ASortingArrayBuilder::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASortingArrayBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

