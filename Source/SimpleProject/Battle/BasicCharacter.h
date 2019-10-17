// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

UENUM(BlueprintType)
enum class EBasicState : uint8
{
	LOCO	UMETA(DisplayName = "Locomotion"),
	ATTACK	UMETA(DisplayName = "Attack"),
	HIT		UMETA(DisplayName = "HIT"),
	DEATH	UMETA(DisplayName = "Death")
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> TraceQuery;

	// Input Actions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	//void Jump();
	void Attack1();
	bool bIsAttackAvailable;

	// Character State
	EBasicState CurrentState;

	// Character HP
	float MaxHP = 100.f;
	float CurrentHP;

	// StimuliSource
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAIPerceptionStimuliSourceComponent* StimuliSource;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
