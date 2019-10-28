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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* Spring;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	// TraceSetting in BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> TraceQuery;

	// Character Status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float MaxHP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float IdleMaxWalkSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float AttackMaxWalkSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float OtherMaxWalkSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	FRotator IdleRotationRate = FRotator(360.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	FRotator AttackRotationRate = FRotator(120.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	FRotator OtherRotationRate = FRotator(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	EBasicState CurrentState;

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

	// Attack Function
	void PrimaryShot();
	void RAbilityShot();
	void QAbilityShot();
	void ShotArrow(FVector& TargetLocation);
	bool bIsAttackAvailable;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Change State
	void SetCurrentState(EBasicState NewState);

	// Arrow Setting in BP
	UPROPERTY(EditAnywhere, Category = "Arrow")
	TSubclassOf<class ABasicArrow> Arrow_Template;

	//UPROPERTY(EditAnywhere, Category = "Rocket")
		//TSubclassOf<class AMyRocket> Rocket_Template;
};
