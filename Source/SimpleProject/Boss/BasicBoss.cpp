// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBoss.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Battle/DamageType/BasicMonsterDamageType.h"

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

	AreaAttack->bAutoDeactivate = true;
	GroundAttack->bAutoDeactivate = true;

	BossState = EBossState::Intro;

	MaxHP = 1000;
	CurrentHP = MaxHP;

	bReplicates = true;
}

void ABasicBoss::FunctionOfAttack(EBossState& NewAttackState)
{
	
}

void ABasicBoss::S2A_FunctionOfAttack_Implementation(const EBossState & NewAttackState)
{
	BossState = NewAttackState;
	switch (BossState)
	{
	case EBossState::TarnadoAttack:
		for (auto i : Players)
		{
			FVector SpawnLocation = i->GetActorLocation() + FVector(0.f, 0.f, -500.f);
			UParticleSystemComponent* TornadoParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TornadoAttack, SpawnLocation);
			Tornados.Add(TornadoParticle);
			TornadoVectors.Add(SpawnLocation);

			GetWorldTimerManager().SetTimer(TornadoTimer, this, &ABasicBoss::TornadoTimerFunction, TornadoRepeatTime, true);
			UE_LOG(LogClass, Warning, TEXT("In FunctinofAttack"));
		}
		break;
	case EBossState::AreaAttack:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AreaAttack, GetActorLocation(), GetActorRotation(), FVector(5.0f));
		break;
	case EBossState::GroundAttack:
		if (TargetPlayer)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GroundAttack, GetActorLocation() + FVector(0.f, 0.f, -200.f), FRotator(0.f, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPlayer->GetActorLocation()).Yaw, 0.f), FVector(2.f));
		}
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
	if (TornadoFlag < 50)
	{
		TornadoFlag++;
		for (auto i : Tornados)
		{
			if (i)
			{
				i->AddRelativeLocation(FVector(0.f, 0.f, 10.f));
			}
		}
		for (auto i : TornadoVectors)
		{
			//i->AddActorWorldTransform(FTransform(FRotator(0.f, 0.f, 0.f), FVector(0.f, 0.f, 10.f)));
			TArray<AActor*> IgnoreActors;
			IgnoreActors.Add(this);
			UGameplayStatics::ApplyRadialDamage(GetWorld(), 1.f, i + FVector(0.f, 0.f,TornadoFlag * 10), 100.f, UBasicMonsterDamageType::StaticClass(), IgnoreActors);
			
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TornadoTimer);
		TornadoFlag = 0;
		for (auto i : Tornados)
		{
			if (i)
			{
				i->Deactivate();
			}
		}
		
		Tornados.Empty();
		TornadoVectors.Empty();
	}
	if (TornadoFlag > 30)
	{

		
	}
}
