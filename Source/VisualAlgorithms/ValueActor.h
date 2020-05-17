// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ValueActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UTextRenderComponent;


UCLASS()
class VISUALALGORITHMS_API AValueActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AValueActor();

public:

	UPROPERTY(VisibleAnywhere, Category = "ValueActor")
		UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "ValueActor")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category = "ValueActor")
		UTextRenderComponent* ValueText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
