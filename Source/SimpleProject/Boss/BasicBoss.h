// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BasicMonster.h"
#include "BasicBoss.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicBoss : public ABasicMonster
{
	GENERATED_BODY()
	
public:
	void FunctionOfAttack();
};
