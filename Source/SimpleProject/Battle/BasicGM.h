// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BasicGM.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABasicGM();
	virtual void BeginPlay() override;

	void WorldTravelFunc();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int PartyNumber = 0;

	// Number of Monster to Clear Level - Not Used
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int NumberOfDefeat = 10;
	// Max Spawn Monster Number
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int MaxMonsterNumber = 10;
	// Spawn Monster Late per Seconds (1~5)
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SpawnLate;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Spawn Monster
	FTimerHandle SpawnTimer;
	UFUNCTION()
	void SpawnFunction();

	//class ABasicMonster* Monster;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class ABasicMonster> MonsterClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class ABasicAIController> MonsterAIClass;
};
