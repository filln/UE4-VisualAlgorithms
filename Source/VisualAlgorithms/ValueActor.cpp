// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AValueActor::AValueActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(GetRootComponent());

	ValueText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ValueText"));
	ValueText->SetupAttachment(GetRootComponent());
	ValueText->SetText(FText::FromString(TEXT("0")));

}

// Called when the game starts or when spawned
void AValueActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AValueActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

