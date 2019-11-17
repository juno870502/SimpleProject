// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicTornadoBossAttack.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"

void ABasicTornadoBossAttack::BeginPlay()
{
	Super::BeginPlay();

	BaseDamage = 1.f;
	//DamagePoint = GetActorLocation() - FVector(0.f, 0.f, -500.f);
	if (HasAuthority())
	{
		AddActorLocalOffset(FVector(0.f, 0.f, -500.f));
	}
}

void ABasicTornadoBossAttack::AttackTimerFunction()
{
	AddActorLocalOffset(FVector(0.f, 0.f, 10.f));
	UGameplayStatics::ApplyRadialDamage(GetWorld(), BaseDamage, GetActorLocation(), 100.f, DamageType, Ignores, GetOwner());
	if (AttackTimerFlag >= 40)
	{
		Particle->Deactivate();
	}
	if (AttackTimerFlag++ >= 50)
	{
		GetWorldTimerManager().ClearTimer(AttackTimer);
		AttackTimerFlag = 0.f;
		Destroy();
	}
}
