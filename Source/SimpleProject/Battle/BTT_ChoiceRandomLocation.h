// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ChoiceRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBTT_ChoiceRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	int a;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
