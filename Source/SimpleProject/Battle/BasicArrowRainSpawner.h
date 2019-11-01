// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BasicArrow.h"
#include "BasicArrowRainSpawner.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicArrowRainSpawner : public ABasicArrow
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;


	UFUNCTION()
	void SpawnFunction();

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ArrowRain;
};
