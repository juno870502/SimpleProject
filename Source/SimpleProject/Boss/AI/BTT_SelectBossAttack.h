// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Boss/BasicBoss.h"
#include "BTT_SelectBossAttack.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBTT_SelectBossAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBossState SelectedState;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
