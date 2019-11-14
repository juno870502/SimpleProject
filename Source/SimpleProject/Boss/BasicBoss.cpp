// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBoss.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ABasicBoss::ABasicBoss()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(200.f);
	GetCapsuleComponent()->SetCapsuleRadius(100.f);
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetMesh()->SetCollisionProfileName(TEXT("MonsterProf"));

	GetMesh()->SetRelativeLocation(FVector(1.0f, 1.0f, -200.f));

	TornadoAttack = CreateDefaultSubobject<UParticleSystem>(TEXT("Tornade"));
	AreaAttack = CreateDefaultSubobject<UParticleSystem>(TEXT("Area"));
	GroundAttack = CreateDefaultSubobject<UParticleSystem>(TEXT("Ground"));
	FireAttack = CreateDefaultSubobject<UParticleSystem>(TEXT("Fire"));

	BossState = EBossState::Intro;

	MaxHP = 1000;
	CurrentHP = MaxHP;
}

void ABasicBoss::FunctionOfAttack()
{
	switch (BossState)
	{
	case EBossState::TarnadoAttack:
		for (auto i : Players)
		{
			FVector SpawnLocation = i->GetActorLocation() - 100.f;
			Tornados.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TornadoAttack, GetActorLocation()));
			GetWorldTimerManager().SetTimer(TornadoTimer, this, &ABasicBoss::TornadoTimerFunction, 0.1f, true);
		}
		break;
	case EBossState::AreaAttack:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AreaAttack, GetActorLocation());
		break;
	case EBossState::GroundAttack:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GroundAttack, GetActorLocation());
		break;
	case EBossState::Fire1:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireAttack, GetActorLocation());
		break;
	case EBossState::Fire2:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireAttack, GetActorLocation());
		break;
	}
}

void ABasicBoss::S2A_DeathFunction_Implementation()
{
}

void ABasicBoss::TornadoTimerFunction()
{
	if (TornadoFlag < 10)
	{
		TornadoFlag++;
		for (auto i : Tornados)
		{
			i->AddRelativeLocation(FVector(0.f, 0.f, 10.f));
		}
	}
	else
	{
		TornadoFlag = 0;
		GetWorldTimerManager().ClearTimer(TornadoTimer);
	}
}
