// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BasicGS.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, ReplicatedUsing = "OnRep_NumOfDeath")
	int NumOfDeathMonsters = 0;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, ReplicatedUsing = "OnRep_NumOfGoal")
	int GoalOfKilledMonsters;

	// This Function Call PublicMSG. and if Kill number over Goal number, set msg fixing
	UFUNCTION()
	void OnRep_NumOfDeath();

	UFUNCTION()
	void OnRep_NumofGoal();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetNumOfDeathMonsters(int Number);
	int GetNumOfDeathMonsters();
};
