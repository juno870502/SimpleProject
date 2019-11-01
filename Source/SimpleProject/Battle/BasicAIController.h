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
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UAISenseConfig_Hearing* Hearing;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UAISenseConfig_Damage* Damaging;

	// Initialize AI (Change BlackBoard Key Values)
	void InitializeAI();

	// Set Home Location
	void SetHomeLocation(FVector NewLocation);

	// Sense Sight Config Values
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AI")
	float SightRadiusValue = 1000.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AI")
	float LoseSightRadiusValue = 1200.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AI")
	float SightAngleValue = 60.f;
	// Sense Hearing Config Values
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AI")
	float HearingRange = 600.f;

	// GenericTeamID & Judge TeamAttitude
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AI")
	FGenericTeamId TeamID = 5;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	// OnPerceptionUpdated Delegate
	UFUNCTION()
	void SenseStuff(const TArray<AActor*>& UpdatedActors);

	// Set Pawn State
	void SetPawnState(EMonsterState NewState);
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AActor* ClosestTargetActor;

	// In Death, Respawn Function
	void Respawn();
};
