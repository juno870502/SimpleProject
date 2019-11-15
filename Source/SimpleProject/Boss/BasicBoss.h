// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BasicMonster.h"
#include "BasicBoss.generated.h"

UENUM()
enum class EBossState : uint8
{
	Intro			UMETA(DisplayName = "Intro"),
	TarnadoAttack	UMETA(DisplayName = "TornadoAttack"),
	AreaAttack		UMETA(DisplayName = "AreaAttack"),
	GroundAttack	UMETA(DisplayName = "GroundAttack"),
	Fire1			UMETA(DisplayName = "Fire1"),
	Fire2			UMETA(DisplayName = "Fire2"),
	Death			UMETA(DisplayName = "Death")
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
	EBossState BossState;
	//virtual void S2A_DeathFunction() override;
	virtual void S2A_DeathFunction_Implementation() override;

	// All Players
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<class AActor*> Players;
	// Target Player
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class AActor* TargetPlayer;

	// Spawn Emitters from Attack
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* TornadoAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* AreaAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* GroundAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* FireAttack;

	FTimerHandle TornadoTimer;
	TArray<class UParticleSystemComponent*> Tornados;
	UFUNCTION()
	void TornadoTimerFunction();
	int8 TornadoFlag = 0;
};
