// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBoss.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Boss/Attack/BasicBossAttack.h"
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

	BossState = EBossState::Intro;

	MaxHP = 1000;
	CurrentHP = MaxHP;

	bReplicates = true;
}

void ABasicBoss::FunctionOfAttack(EBossState& NewAttackState)
{
	if (HasAuthority())
	{
		BossState = NewAttackState;
		FActorSpawnParameters Param;
		Param.Owner = this;
		switch (BossState)
		{
		case EBossState::TarnadoAttack:
			for (auto i : Players)
			{
				//FVector SpawnLocation = i->GetActorLocation() + FVector(0.f, 0.f, -500.f);
				//UParticleSystemComponent* TornadoParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TornadoAttack, SpawnLocation);
				//Tornados.Add(TornadoParticle);
				//TornadoVectors.Add(SpawnLocation);
				//GetWorldTimerManager().SetTimer(TornadoTimer, this, &ABasicBoss::TornadoTimerFunction, TornadoRepeatTime, true);
				GetWorld()->SpawnActor<ABasicBossAttack>(TornadoAttack, i->GetActorLocation(), i->GetActorRotation(), Param);
				UE_LOG(LogClass, Warning, TEXT("In TornadoAttack"));
			}
			break;
		case EBossState::AreaAttack:
			GetWorld()->SpawnActor<ABasicBossAttack>(AreaAttack, GetActorTransform(), Param);
			break;
		case EBossState::GroundAttack:
			if (TargetPlayer)
			{
				GetWorld()->SpawnActor<ABasicBossAttack>(GroundAttack, GetActorTransform(), Param);
			}
			break;
		case EBossState::Fire1:
			if (TargetPlayer)
			{
				GetWorld()->SpawnActor<ABasicBossAttack>(FireAttack, GetMesh()->GetSocketTransform(TEXT("Muzzle_Front")), Param);
			}
			break;
		case EBossState::Fire2:
			if (TargetPlayer)
			{
				GetWorld()->SpawnActor<ABasicBossAttack>(FireAttack, GetMesh()->GetSocketTransform(TEXT("Muzzle_Front")), Param);
			}
			break;
		}
	}
}

void ABasicBoss::S2A_FunctionOfAttack_Implementation(const EBossState & NewAttackState)
{
	
}

void ABasicBoss::S2A_DeathFunction_Implementation()
{
}
