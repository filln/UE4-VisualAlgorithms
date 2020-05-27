// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

/*
The actor is a platform for ValueActor. Show in scene index of ValueActor in SortingArray.
Pivot of the Mesh must be above for superposition IndexActor and ValueActor.

*/

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

	//The platform for ValueActor. Pivot of the Mesh must be above for superposition IndexActor and ValueActor.
	UPROPERTY(VisibleAnywhere, Category = "IndexActor")
		UStaticMeshComponent* Mesh;

	//This text show index of SortingArray.
	UPROPERTY(VisibleAnywhere, Category = "IndexActor")
		UTextRenderComponent* IndexText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
