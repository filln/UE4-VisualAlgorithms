// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class ASortingAlgorithms;
class AAlgorithmsManager;
class ASortingArrayBuilder;
class ADataAlgorithms;
UCLASS()
class VISUALALGORITHMS_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	//Public UFUNCTION() functions.
public:

	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		ASortingAlgorithms* GetSortingAlgorithms() const;
	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		AAlgorithmsManager* GetAlgorithmsManager() const;
	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		ASortingArrayBuilder* GetSortingArrayBuilder() const;
	UFUNCTION(BlueprintCallable, Category = "VisualAlgorithms")
		ADataAlgorithms* GetDataAlgorithms() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
