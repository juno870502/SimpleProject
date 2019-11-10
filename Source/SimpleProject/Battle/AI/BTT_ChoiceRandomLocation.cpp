// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChoiceRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Battle/BasicAIController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTT_ChoiceRandomLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABasicAIController* AIC = Cast<ABasicAIController>(OwnerComp.GetAIOwner());

	UNavigationSystemV1* NavV1 = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

	FNavLocation TargetVec;
	if (AIC && NavV1)
	{
		NavV1->GetRandomPointInNavigableRadius(OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomeLocation")), 500.f, TargetVec);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), TargetVec);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
	
}
