// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Battle/BasicMonster.h"
#include "MonNotifySetState.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UMonNotifySetState : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EMonsterState NewState;
};
