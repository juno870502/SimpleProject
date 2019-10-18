// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Battle/BasicMonster.h"
#include "BTT_ChangeCurrentState.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBTT_ChangeCurrentState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EMonsterState ChangeState = EMonsterState::LOCO;
};
