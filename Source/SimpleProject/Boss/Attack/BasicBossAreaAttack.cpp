// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBossAreaAttack.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


void ABasicBossAreaAttack::BeginPlay()
{
	Super::BeginPlay();

	Particle->SetRelativeScale3D(FVector(10.f));
	BaseDamage = 1.f;
}

void ABasicBossAreaAttack::AttackTimerFunction()
{
	AttackTimerFlag++;
	if (AttackTimerFlag > 5.f)
	{
		
	}
	if (AttackTimerFlag == 10.f)
	{
		DamagePoint = GetActorLocation();
		FVector EndPoint = DamagePoint + FVector(1.f);
		TArray<FHitResult> Hits;
		UKismetSystemLibrary::SphereTraceMulti(GetWorld(), DamagePoint, EndPoint, 1500.f, ETraceTypeQuery::TraceTypeQuery4, false, Ignores, EDrawDebugTrace::ForDuration, Hits, true);
		for (auto i : Hits)
		{
			UGameplayStatics::ApplyDamage(i.GetActor(), BaseDamage, nullptr, GetOwner(), DamageType);
		}
		Particle->Deactivate();
	}
	if (AttackTimerFlag > 15.f)
	{
		Destroy();
		AttackTimerFlag = 0.f;
	}
}
