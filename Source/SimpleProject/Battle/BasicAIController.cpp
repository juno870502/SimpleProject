// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/KismetMathLibrary.h"
#include "Battle/BasicMonster.h"

ABasicAIController::ABasicAIController()
{
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = SightRadiusValue;
	Sight->LoseSightRadius = LoseSightRadiusValue;
	Sight->PeripheralVisionAngleDegrees = SightAngleValue;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
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
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &ABasicAIController::SenseStuff);
}

void ABasicAIController::SenseStuff(const TArray<AActor*>& UpdatedActors)
{
	//UE_LOG(LogClass, Warning, TEXT("SizeOfActors : %d"), UpdatedActors.Num());
	TArray<AActor*> PerceivedActors;
	AIPerception->GetCurrentlyPerceivedActors(NULL, PerceivedActors);
	float MinDistance = 9999.f;
	ClosestTargetActor = nullptr;
	for (auto i : PerceivedActors)
	{
		if (i->IsValidLowLevel())
		{
			float TempDistance = UKismetMathLibrary::Vector_Distance(GetPawn()->GetActorLocation(), i->GetActorLocation());
			if (TempDistance < MinDistance)
			{
				MinDistance = TempDistance;
				ClosestTargetActor = i;
			}
		}
	}
	if (ClosestTargetActor->IsValidLowLevel())
	{
		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), ClosestTargetActor);
		Cast<ABasicMonster>(GetPawn())->SetCurrentState(EMonsterState::CHASE);
	}
}

void ABasicAIController::SetPawnState(EMonsterState NewState)
{
	ABasicMonster* Monster = Cast<ABasicMonster>(GetPawn());
	if (Monster)
	{
		Monster->SetCurrentState(NewState);
	}
}
