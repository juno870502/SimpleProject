// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BasicMonster.h"
#include "BasicBoss.generated.h"

UENUM()
enum class EBossAttack : uint8
{
	AttackSpecial1	UMETA(DisplayName = "AS1"),
	AreaAttack		UMETA(DisplayName = "AreaAttack"),
	GroundAttack	UMETA(DisplayName = "GroundAttack"),
	Fire1			UMETA(DisplayName = "Fire1"),
	Fire2			UMETA(DisplayName = "Fire2")
};
/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicBoss : public ABasicMonster
{
	GENERATED_BODY()
	
public:

	ABasicBoss();
	void FunctionOfAttack();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Phase = 1;
	//virtual void S2A_DeathFunction() override;
	virtual void S2A_DeathFunction_Implementation() override;
};
