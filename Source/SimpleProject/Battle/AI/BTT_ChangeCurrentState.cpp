// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChangeCurrentState.h"
#include "Battle/BasicMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_ChangeCurrentState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicMonster* Mon = Cast<ABasicMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (Mon->IsValidLowLevel())
	{
		Mon->SetCurrentState(ChangeState);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
	
}
