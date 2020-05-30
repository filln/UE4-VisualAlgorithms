// Copyright 2020 Anatoli Kucharau. All Rights Reserved.


#include "SortingArrayBuilder.h"
#include "VisualAlgorithmsGameModeBase.h"
#include "IndexActor.h"
#include "ValueActor.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ASortingArrayBuilder::ASortingArrayBuilder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountOfElements = 10;
	BeginLocation = FVector(0.f);
	DeltaLocation = FVector(0.f, 100.f, 5.f);

	IndexActorClass = AIndexActor::StaticClass();
	ValueActorClass = AValueActor::StaticClass();

}

void ASortingArrayBuilder::BuildSortingArray()
{
	SortingArray.Empty();
	for (size_t index = 0; index < CountOfElements; index++)
	{
		SortingArray.Add(index);
	}
}

void ASortingArrayBuilder::BuildVisibleArray()
{
	IndexActorsArray.Empty();
	ValueActorsArray.Empty();

	FVector SpawnLocation = BeginLocation;
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	//This block spawn actors, save its index and value in SortingArray to tag, fill visible index or value (UTextRenderComponent), add spawned actor to array.
	for (size_t index = 0; index < SortingArray.Num(); index++)
	{
		AIndexActor* CurrentIndexActor = GetWorld()->SpawnActor<AIndexActor>(IndexActorClass, SpawnLocation, FRotator(0.f), SpawnParam);
		FString StrIndex = FString::FromInt(index);
		FText VisibleIndex = FText::FromString(StrIndex);
		CurrentIndexActor->IndexText->SetText(VisibleIndex);
		FName TagIndex = FName(*StrIndex);
		CurrentIndexActor->Tags.Add(TagIndex);
		IndexActorsArray.Add(CurrentIndexActor);


		AValueActor* CurrentValueActor = GetWorld()->SpawnActor<AValueActor>(ValueActorClass, SpawnLocation, FRotator(0.f), SpawnParam);
		FString StrValue = FString::FromInt(SortingArray[index]);
		FText VisibleValue = FText::FromString(StrValue);
		CurrentValueActor->ValueText->SetText(VisibleValue);
		FName TagValue = FName(*StrValue);
		CurrentValueActor->Tags.Add(TagValue);
		ValueActorsArray.Add(CurrentValueActor);

		SpawnLocation += DeltaLocation;
	}

}


void ASortingArrayBuilder::DestroySortAndVisibleArrays()
{
	for (size_t index = 0; index < SortingArray.Num(); index++)
	{
		IndexActorsArray[index]->Destroy();
		ValueActorsArray[index]->Destroy();
	}
	IndexActorsArray.Empty();
	ValueActorsArray.Empty();
	SortingArray.Empty();

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


