// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"
#include "Boss/BasicBoss.h"
#include "Perception/AIPerceptionComponent.h"

void ABossAIController::SenseStuff(const TArray<AActor*>& UpdatedActors)
{
	ABasicBoss* Boss = Cast<ABasicBoss>(GetPawn());
	int32 MaxRandomNumber = 0;

	if (Boss)
	{
		AIPerception->GetCurrentlyPerceivedActors(NULL, Boss->Players);
		FMath::Clamp<int32>(MaxRandomNumber, 0, Boss->Players.Num() - 1);
		Boss->TargetPlayer = Boss->Players[FMath::RandRange(0, MaxRandomNumber)];
	}
}
