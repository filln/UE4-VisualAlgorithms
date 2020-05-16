// Fill out your copyright notice in the Description page of Project Settings.


#include "IndexActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AIndexActor::AIndexActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

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

