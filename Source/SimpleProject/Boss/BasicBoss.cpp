// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBoss.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Boss/Attack/BasicBossAttack.h"
#include "Boss/BossAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Battle/DamageType/BasicMonsterDamageType.h"
#include "Battle/DamageType/BasicArrowRainDamageType.h"

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
		S2A_SetCurrentState(EMonsterState::ATTACK);
		BossState = NewAttackState;
		FActorSpawnParameters Param;
		Param.Owner = this;
		S2A_FunctionOfAttack(BossState);
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
	switch (NewAttackState)
	{
	
	case EBossState::TarnadoAttack:
		PlayAnimMontage(AttackMontage, 1.0f, TEXT("AS1"));
		break;
	case EBossState::AreaAttack:
		PlayAnimMontage(AttackMontage, 1.0f, TEXT("AS2"));
		break;
	case EBossState::GroundAttack:
		PlayAnimMontage(AttackMontage, 1.0f, TEXT("AS3"));
		break;
	case EBossState::Fire1:
		PlayAnimMontage(AttackMontage, 1.0f, TEXT("Fire"));
		break;
	case EBossState::Fire2:
		PlayAnimMontage(AttackMontage, 1.0f, TEXT("Fire"));
		break;
	}
}

void ABasicBoss::S2A_DeathFunction_Implementation()
{
}

float ABasicBoss::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	//Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	switch (DamageEvent.GetTypeID())
	{
	case FDamageEvent::ClassID:
		if (DamageEvent.DamageTypeClass == UBasicArrowRainDamageType::StaticClass())
		{
			// Boss is Too Big so take 1/5 damage
			CurrentHP -= Damage / 5;
			UE_LOG(LogClass, Warning, TEXT("Boss Current HP : %f"), CurrentHP);
			if (CurrentHP <= 0)
			{
				S2A_SetCurrentState(EMonsterState::DEATH);
				S2A_DeathFunction();
			}
			else
			{
				S2A_SetCurrentState(EMonsterState::HIT);
			}
			S2A_UpdateWidget(CurrentHP / MaxHP, Damage / 5);
		}
		break;
	case FRadialDamageEvent::ClassID:
		
		if (DamageEvent.DamageTypeClass == UBasicArrowRainDamageType::StaticClass())
		{
			// Boss is Too Big so take 1/5 damage
			CurrentHP -= Damage/5;
			UE_LOG(LogClass, Warning, TEXT("Boss Current HP : %f"), CurrentHP);
			if (CurrentHP <= 0)
			{
				S2A_SetCurrentState(EMonsterState::DEATH);
				S2A_DeathFunction();
			}
			else
			{
				S2A_SetCurrentState(EMonsterState::HIT);
			}
			S2A_UpdateWidget(CurrentHP / MaxHP, Damage/5);
		}
		break;
	case FPointDamageEvent::ClassID:
		if (DamageEvent.DamageTypeClass != UBasicMonsterDamageType::StaticClass())
		{
			//DamageEvent.DamageTypeClass.
			CurrentHP -= Damage;
			UE_LOG(LogClass, Warning, TEXT("Boss Current HP : %f"), CurrentHP);
			if (CurrentHP <= 0)
			{
				S2A_SetCurrentState(EMonsterState::DEATH);
				S2A_DeathFunction();
			}
			else
			{
				S2A_SetCurrentState(EMonsterState::HIT);
			}
			S2A_UpdateWidget(CurrentHP / MaxHP, Damage);
		}
		const FPointDamageEvent* PDE = (FPointDamageEvent*)&DamageEvent;
		LaunchCharacter(PDE->ShotDirection * 1000.f, true, true);
		break;
	}
	if (CurrentHP < MaxHP/2)
	{
		ABossAIController* BAIC = Cast<ABossAIController>(GetController());
		BAIC->SetPhase(1);
	}

	return Damage;
}
