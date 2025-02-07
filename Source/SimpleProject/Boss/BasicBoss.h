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
	void FunctionOfAttack(EBossState& NewAttackState);

	//S2A Function
	UFUNCTION(NetMulticast, Reliable)
	void S2A_FunctionOfAttack(const EBossState& NewAttackState);
	void S2A_FunctionOfAttack_Implementation(const EBossState& NewAttackState);

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
	// This is Not Work... Depricated
	/*UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* TornadoAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* AreaAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* GroundAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* FireAttack;*/

	// Spawn Attack Actor
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class ABasicBossAttack> TornadoAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class ABasicBossAttack> AreaAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class ABasicBossAttack> GroundAttack;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class ABasicBossAttack> FireAttack;

	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;
};
