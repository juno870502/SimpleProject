// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

UENUM(BlueprintType)
enum class EBasicState : uint8
{
	LOCO			UMETA(DisplayName = "Locomotion"),
	PrimaryShot		UMETA(DisplayName = "PrimaryShot"),
	RAbilityShot	UMETA(DisplayName = "RAbilityShot"),
	QAbilityShot	UMETA(DisplayName = "QAbilityShot"),
	HIT				UMETA(DisplayName = "HIT"),
	DEATH			UMETA(DisplayName = "Death")
};

UCLASS()
class SIMPLEPROJECT_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Character Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* Spring;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAudioComponent* ShotArrowSound;

	// TraceSetting in BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> TraceQuery;

	// Character Status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float MaxHP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float MaxMP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float CurrentMP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float IdleMaxWalkSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float AttackMaxWalkSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float OtherMaxWalkSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	FRotator IdleRotationRate = FRotator(0.f, 180.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	FRotator AttackRotationRate = FRotator(0.f, 120.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	FRotator OtherRotationRate = FRotator(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	EBasicState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float RAbilityConsumption = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
		float QAbilityConsumption = 50.f;
	// Change Charactre MP
	void SetCurrentMP(float NewMP);

	// StimuliSource
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAIPerceptionStimuliSourceComponent* StimuliSource;


public:


	// Input Actions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void PressJump();

	// Attack Input Function Timer
	FTimerHandle InputTimerHandle;
	FTimerHandle ChargeTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float ResetATKTime = 0.01f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	int InputFlag = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	int ChargeFlag = 0;

	UFUNCTION()
	void LeftClick();
	UFUNCTION()
	void LeftRelease();
	UFUNCTION()
	void RightClick();
	UFUNCTION()
	void InputTimerFunc();
	UFUNCTION()
	void ChargeTimerFunc();
	
	// C2S Attack Function - Pre Function call to Server Multicast
	// Plus, Attack Available Check Process
	UFUNCTION(Server, Reliable)
	void C2S_MainAttackFunc(const EBasicState& AttackState);
	void C2S_MainAttackFunc_Implementation(const EBasicState& AttackState);
	// S2A Attack Function
	UFUNCTION(NetMulticast, Reliable)
	void S2A_MainAttackFunc(const EBasicState& AttackState);
	void S2A_MainAttackFunc_Implementation(const EBasicState& AttackState);

	bool bIsAttackAvailable;

	// Spawn Arrow
	void ShotArrow(const FVector& TargetLocation);

	// Function to Available Attack
	void SetAttackAvailability(bool NewAvailable);

	// Take Damage
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Change State
	void SetCurrentState(EBasicState NewState);

	// Arrow Setting in BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class ABasicArrow> PrimaryArrow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class ABasicArrow> RAbilityArrow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class ABasicArrow> QAbilityArrow;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	class UAnimMontage* AttackMontage;
};
