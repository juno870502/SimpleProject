// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Boss/Attack/BasicBossAttack.h"
#include "BasicTornadoBossAttack.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicTornadoBossAttack : public ABasicBossAttack
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;
	virtual void AttackTimerFunction() override;
};
