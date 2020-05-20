// Copyright 2020 Anatoli Kucharau. All Rights Reserved.


#include "IndexActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AIndexActor::AIndexActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(GetRootComponent());

	IndexText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IndexText"));
	IndexText->SetupAttachment(GetRootComponent());
	IndexText->SetText(FText::FromString(TEXT("0")));

}

// Called when the game starts or when spawned
void AIndexActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndexActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

