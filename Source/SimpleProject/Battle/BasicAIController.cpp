// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Kismet/KismetMathLibrary.h"
#include "Battle/BasicMonster.h"
#include "Battle/BasicPlayerController.h"
#include "Battle/BasicCharacter.h"
#include "NavigationSystem.h"

ABasicAIController::ABasicAIController()
{
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	// AISense Sight Config
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = SightRadiusValue;
	Sight->LoseSightRadius = LoseSightRadiusValue;
	Sight->PeripheralVisionAngleDegrees = SightAngleValue;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*Sight);

	// AISense Hearing Config
	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing"));
	Hearing->HearingRange = HearingRange;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*Hearing);

	// AISense Damage Config
	Damaging = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage"));
	GetPerceptionComponent()->ConfigureSense(*Damaging);
	
	// SetTeam ID
	SetGenericTeamId(TeamID);
}

void ABasicAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ABasicAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	// Setup BB & BT
	UseBlackboard(BB, BBComponent);
	RunBehaviorTree(BT);

	if (GetPawn())
	{
		SetHomeLocation(GetPawn()->GetActorLocation());
	}

	// Setup AIPerception
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &ABasicAIController::SenseStuff);
}

void ABasicAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABasicAIController::InitializeAI()
{
	BBComponent->ClearValue(TEXT("HomeLocation"));
	BBComponent->ClearValue(TEXT("TargetActor"));
	SetHomeLocation(GetPawn()->GetActorLocation());
	if (ClosestTargetActor->IsValidLowLevel())
	{
		ClosestTargetActor = NULL;
	}
}

void ABasicAIController::SetHomeLocation(FVector NewLocation)
{
	if (BB && BBComponent && BT)
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("HomeLocation"), NewLocation);
	}
}

ETeamAttitude::Type ABasicAIController::GetTeamAttitudeTowards(const AActor & Other) const
{	
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			if (GetGenericTeamId() == TeamAgent->GetGenericTeamId())
			{
				return ETeamAttitude::Friendly;
			}
		}
	}
	return ETeamAttitude::Neutral;
}

FGenericTeamId ABasicAIController::GetGenericTeamId() const
{
	return TeamID;
}

void ABasicAIController::SenseStuff(const TArray<AActor*>& UpdatedActors)
{
	// Choose Currently Perceived Actors
	TArray<AActor*> PerceivedActors;
	AIPerception->GetCurrentlyPerceivedActors(NULL, PerceivedActors);

	float MinDistance = 9999.f;
	ClosestTargetActor = nullptr;
	for (auto i : PerceivedActors)
	{
		if (i->IsValidLowLevel())
		{
			if (GetTeamAttitudeTowards(*i) != ETeamAttitude::Friendly)
			{
				float TempDistance = UKismetMathLibrary::Vector_Distance(GetPawn()->GetActorLocation(), i->GetActorLocation());
				if (TempDistance < MinDistance)
				{
					MinDistance = TempDistance;
					ClosestTargetActor = i;
				}
			}
		}
	}
	if (ClosestTargetActor->IsValidLowLevel())
	{
		BBComponent->SetValueAsObject(TEXT("TargetActor"), ClosestTargetActor);
		Cast<ABasicMonster>(GetPawn())->S2A_SetCurrentState(EMonsterState::CHASE);
	}
}

void ABasicAIController::SetPawnState(EMonsterState NewState)
{
	ABasicMonster* Monster = Cast<ABasicMonster>(GetPawn());
	if (Monster)
	{
		Monster->S2A_SetCurrentState(NewState);
	}
}

void ABasicAIController::Respawn()
{
	// Set Random Respawn Location from Home Vecotr
	FVector OriginVec = BBComponent->GetValueAsVector(TEXT("HomeLocation"));
	FNavLocation TargetVec;
	Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem())->GetRandomPointInNavigableRadius(OriginVec, 3000.f, TargetVec);
	GetPawn()->SetActorLocation(TargetVec);
	
	// Monster Initialize
	ABasicMonster* Mon = Cast<ABasicMonster>(GetPawn());
	if (Mon->IsValidLowLevel())
	{
		Mon->InitializeValues();
	}

	// AI Initialize
	InitializeAI();
}

