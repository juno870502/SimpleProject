// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Battle/BasicMonster.h"
#include "BasicMinionAnim.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBasicMinionAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStatus")
	float ABPVelocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStatus")
	EMonsterState ABPCurrentState;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
