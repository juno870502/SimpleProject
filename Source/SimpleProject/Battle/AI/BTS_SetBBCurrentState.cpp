// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SetBBCurrentState.h"
#include "AIController.h"
#include "Battle/BasicMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Battle/BasicMonster.h"

void UBTS_SetBBCurrentState::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ABasicMonster* Mon = Cast<ABasicMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (Mon->IsValidLowLevel())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)Mon->CurrentState);
	}
	
}
