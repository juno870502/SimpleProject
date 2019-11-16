// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SelectBossAttack.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_SelectBossAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABasicBoss* Boss = Cast<ABasicBoss>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss)
	{
		Boss->FunctionOfAttack(SelectedState);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
