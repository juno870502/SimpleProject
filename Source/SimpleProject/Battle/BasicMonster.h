// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicMonster.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	SPAWN	UMETA(DisplayName = "Spawn"),
	LOCO	UMETA(DisplayName = "Locomotion"),
	CHASE	UMETA(DisplayName = "Chase"),
	ATTACK	UMETA(DisplayName = "Attack"),
	HIT		UMETA(DisplayName = "HIT"),
	DEATH	UMETA(DisplayName = "Death")
};

UCLASS()
class SIMPLEPROJECT_API ABasicMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Take Damage (Need Sync)
	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	// Monster Status
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
	float MaxHP = 100.f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
	float CurrentHP;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
	float AttackRange = 800.f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
	float ChaseRange = 2000.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	EMonsterState CurrentState;

	// Change State
	// Server Call Multicast
	UFUNCTION(NetMulticast, Reliable)
	void S2A_SetCurrentState(const EMonsterState& NewState);
	void S2A_SetCurrentState_Implementation(const EMonsterState& NewState);

	// AttackMoment
	// Server Call Multicast
	UFUNCTION(NetMulticast, Reliable)
	void S2A_MomentOfAttack();
	void S2A_MomentOfAttack_Implementation();

	// Initialize Values (HP, AttackRange, State etc...)
	void InitializeValues();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TSubclassOf<class ABasicMonProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	class UAnimMontage* AttackMontage;
};
