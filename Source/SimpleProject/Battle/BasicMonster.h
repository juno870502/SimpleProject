// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicMonster.generated.h"

UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	LOCO	UMETA(DisplayName = "Locomotion"),
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


	
};
