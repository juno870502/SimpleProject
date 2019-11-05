// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_AttackFunction.h"
#include "Battle/BasicAIController.h"
#include "Battle/BasicMonster.h"

EBTNodeResult::Type UBTT_AttackFunction::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicAIController* AIC = Cast<ABasicAIController>(OwnerComp.GetAIOwner());
	if (AIC)
	{
		ABasicMonster* Mon = Cast<ABasicMonster>(AIC->GetPawn());
		Mon->S2A_MomentOfAttack();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
