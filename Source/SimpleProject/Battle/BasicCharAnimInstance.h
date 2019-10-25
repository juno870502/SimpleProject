// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Battle/BasicCharacter.h"
#include "BasicCharAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBasicCharAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="CharacterStatus")
	float ABPVelocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStatus")
	float ABPAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStatus")
	EBasicState ABPCurrentState;
};
