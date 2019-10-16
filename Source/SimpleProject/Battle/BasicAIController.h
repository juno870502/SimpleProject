// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Battle/BasicMonster.h"
#include "BasicAIController.generated.h"

/**
 * 
 */

UCLASS()
class SIMPLEPROJECT_API ABasicAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABasicAIController();
	virtual void BeginPlay() override;
	
	// Setup At Blueprint
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBlackboardData* BB;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBehaviorTree* BT;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBlackboardComponent* BBComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UAIPerceptionComponent* AIPerception;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UAISenseConfig_Sight* Sight;

	UFUNCTION()
	void SenseStuff(const TArray<AActor*>& UpdatedActors);

	void SetPawnState(EMonsterState NewState);
};
