// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SelectTargetActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Battle/BasicMonster.h"
#include "AIController.h"

void UBTS_SelectTargetActor::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	ABasicMonster* Mon = Cast<ABasicMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (TargetActor && Mon)
	{
		// In Attack Range -> State::Attack / Out Attack Range -> State::Chase
		if (Mon->AttackRange >= UKismetMathLibrary::Vector_Distance(Mon->GetActorLocation(), TargetActor->GetActorLocation()))
		{
			Mon->S2A_SetCurrentState(EMonsterState::ATTACK);
		}
		else
		{
			Mon->S2A_SetCurrentState(EMonsterState::CHASE);
		}

		// Out Limit Radius -> State::Loco
		if (Mon->ChaseRange < UKismetMathLibrary::Vector_Distance(Mon->GetActorLocation(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomeLocation"))))
		{
			Mon->S2A_SetCurrentState(EMonsterState::LOCO);
		}
	}
	else
	{
		Mon->S2A_SetCurrentState(EMonsterState::LOCO);
	}
}
