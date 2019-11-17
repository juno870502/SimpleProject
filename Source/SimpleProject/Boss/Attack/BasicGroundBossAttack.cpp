// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGroundBossAttack.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void ABasicGroundBossAttack::BeginPlay()
{
	Super::BeginPlay();

	BaseDamage = 1.f;
	if (HasAuthority())
	{
		Particle->AddLocalOffset(FVector(0.f, 0.f, -200.f));
	}
	APawn* Boss = Cast<APawn>(GetOwner());
	DamagePoint = Boss->GetActorLocation() + FVector(0.f, 0.f, -200.f);

	Particle->SetRelativeScale3D(FVector(2.0f));
	EndPoint = DamagePoint;
}

void ABasicGroundBossAttack::AttackTimerFunction()
{
	AttackTimerFlag++;
	
	EndPoint += GetOwner()->GetActorForwardVector() * 150;
	TArray<FHitResult> Hits;
	if (AttackTimerFlag <= 10)
	{
		UKismetSystemLibrary::SphereTraceMulti(GetWorld(), DamagePoint, EndPoint, 150.f, ETraceTypeQuery::TraceTypeQuery4, false, Ignores, EDrawDebugTrace::ForDuration, Hits, true);
		for (auto i : Hits)
		{
			UGameplayStatics::ApplyDamage(i.GetActor(), BaseDamage, nullptr, GetOwner(), DamageType);
		}
	}
	
	if (AttackTimerFlag > 10)
	{
		Particle->Deactivate();
	}
	if (AttackTimerFlag >= 20)
	{
		AttackTimerFlag = 0;
		Destroy();
	}
	DamagePoint = EndPoint;
}
