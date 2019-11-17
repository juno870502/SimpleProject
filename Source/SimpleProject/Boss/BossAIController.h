// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BasicAIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABossAIController : public ABasicAIController
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	virtual void SenseStuff(const TArray<AActor*>& UpdatedActors) override;

	void SetPhase(int8 NewPhase);
};
