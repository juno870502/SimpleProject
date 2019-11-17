// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BasicMinionAnim.h"
#include "Boss/BasicBoss.h"
#include "BasicBossAnim.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBasicBossAnim : public UBasicMinionAnim
{
	GENERATED_BODY()
	
public :

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EBossState AnimBossState;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
