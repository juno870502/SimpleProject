// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ABasicAIController::ABasicAIController()
{
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &ABasicAIController::SenseStuff);
	Sight->SightRadius = 500.f;
	Sight->PeripheralVisionAngleDegrees = 60.f;
	AIPerception->ConfigureSense(*Sight);
}

void ABasicAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BB && BBComponent && BT)
	{
		UseBlackboard(BB, BBComponent);
		RunBehaviorTree(BT);
		GetBlackboardComponent()->SetValueAsVector(TEXT("HomeLocation"), GetPawn()->GetActorLocation());
	}
}

void ABasicAIController::SenseStuff(const TArray<AActor*>& UpdatedActors)
{
}

void ABasicAIController::SetPawnState(EMonsterState NewState)
{
	ABasicMonster* Monster = Cast<ABasicMonster>(GetPawn());
	if (Monster)
	{
		Monster->CurrentState = NewState;
	}
}
