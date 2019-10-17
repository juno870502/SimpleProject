// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_SetBBCurrentState.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBTS_SetBBCurrentState : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName CurrentStateKey;
};
