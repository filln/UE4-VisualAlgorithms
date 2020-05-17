// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IndexActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS()
class VISUALALGORITHMS_API AIndexActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIndexActor();

public:

	UPROPERTY(VisibleAnywhere, Category = "IndexActor")
		UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "IndexActor")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category = "IndexActor")
		UTextRenderComponent* IndexText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};