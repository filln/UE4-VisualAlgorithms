// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ValueActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class VISUALALGORITHMS_API AValueActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AValueActor();

public:

	UPROPERTY(EditDefaultsOnly, Category = "ValueActor")
	UBoxComponent* BoxCollision;
	UPROPERTY(EditDefaultsOnly, Category = "ValueActor")
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
