// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGroundBossAttack.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void ABasicGroundBossAttack::BeginPlay()
{
	Super::BeginPlay();

	
}

void ABasicGroundBossAttack::AttackTimerFunction()
{
	if (AttackTimerFlag++ >= 10)
	{
		AttackTimerFlag = 0;
		Destroy();
	}
}
