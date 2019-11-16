// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBossAttack.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
ABasicBossAttack::ABasicBossAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = Particle;
	Particle->bAutoActivate = false;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABasicBossAttack::BeginPlay()
{
	Super::BeginPlay();
	
	Particle->Activate();
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ABasicBossAttack::AttackTimerFunction, AttackRate, true);
}

// Called every frame
void ABasicBossAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicBossAttack::AttackTimerFunction()
{
}

