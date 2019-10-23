// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Respawn.h"
#include "Battle/BasicAIController.h"

EBTNodeResult::Type UBTT_Respawn::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABasicAIController* AI = Cast<ABasicAIController>(OwnerComp.GetAIOwner());
	if (AI->IsValidLowLevel())
	{
		AI->Respawn();
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
