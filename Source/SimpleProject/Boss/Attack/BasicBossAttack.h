// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicBossAttack.generated.h"

UCLASS()
class SIMPLEPROJECT_API ABasicBossAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicBossAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UParticleSystemComponent* Particle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BaseDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageRadius;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector DamagePoint;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FTimerHandle AttackTimer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackRate = 0.1f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 AttackTimerFlag = 0.f;

	// Need to override.
	UFUNCTION()
	virtual void AttackTimerFunction();
};
