// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

/*
The actor is visual representation value of the SortingArray.
Pivot of the Mesh must be underneath for superposition IndexActor and ValueActor.
*/

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

	//It's the visual representation of the value. Pivot of the Mesh must be underneath for superposition IndexActor and ValueActor.
	UPROPERTY(VisibleAnywhere, Category = "ValueActor")
		UStaticMeshComponent* Mesh;

	//This text show value of the SortingArray.
	UPROPERTY(VisibleAnywhere, Category = "ValueActor")
		UTextRenderComponent* ValueText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
