// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Death.h"
#include "Battle/BasicAIController.h"
#include "Battle/BasicMonster.h"

EBTNodeResult::Type UBTT_Death::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABasicAIController* AIC = Cast<ABasicAIController>(OwnerComp.GetAIOwner());
	if (AIC)
	{
		ABasicMonster* BM = Cast<ABasicMonster>(AIC->GetPawn());
		BM->S2A_DeathFunction();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
