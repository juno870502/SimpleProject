// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"
#include "Boss/BasicBoss.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetBlackboardComponent())
	{
		SetPhase(0);
	}
}

void ABossAIController::SenseStuff(const TArray<AActor*>& UpdatedActors)
{
	ABasicBoss* Boss = Cast<ABasicBoss>(GetPawn());
	int32 MaxRandomNumber = 0;

	if (Boss)
	{
		AIPerception->GetCurrentlyPerceivedActors(NULL, Boss->Players);
		FMath::Clamp<int32>(MaxRandomNumber, 0, Boss->Players.Num() - 1);
		Boss->TargetPlayer = Boss->Players[FMath::RandRange(0, MaxRandomNumber)];
		BBComponent->SetValueAsObject(TEXT("TargetPlayer"), Boss->TargetPlayer);
	}
}

void ABossAIController::SetPhase(int8 NewPhase)
{
	GetBlackboardComponent()->SetValueAsInt(TEXT("Phase"), NewPhase);
}
