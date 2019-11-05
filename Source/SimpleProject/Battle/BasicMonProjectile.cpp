// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMonProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Battle/BasicCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Battle/DamageType/BasicMonsterDamageType.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABasicMonProjectile::ABasicMonProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Basic Components
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	BeamParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Beam"));
	BeamParticle->SetupAttachment(RootComponent);

	// Set Sphere
	Sphere->SetSphereRadius(50.f);
	Sphere->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	Sphere->SetCollisionProfileName(TEXT("MonATK"));
	Sphere->SetGenerateOverlapEvents(true);

	// Set Mesh
	//Mesh->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	//Mesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	//Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	//Mesh->SetGenerateOverlapEvents(false);

	// Set Beam Particle
	BeamParticle->SetRelativeLocation(FVector(-50.f, 0.f, 0.f));
	BeamParticle->SetVectorParameter(TEXT("Source"), GetActorLocation() + FVector(-25.f, 0.f, 0.f));
	BeamParticle->SetVectorParameter(TEXT("Target"), GetActorLocation() + FVector(100.f, 0.f, 0.f));

	// Set projectile movement setting
	Projectile->bRotationFollowsVelocity = true;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->Velocity = FVector(1.0f, 0.f, 0.f);
	Projectile->InitialSpeed = CustomInitSpeed;

	// Hit Explosion Particle
	HitEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("HitEffect"));
}

// Called when the game starts or when spawned
void ABasicMonProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(10.f);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABasicMonProjectile::OnOverlapBegin);
}

// Called every frame
void ABasicMonProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicMonProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Exclude Self Actor
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (Pawn)
	{
		if (OtherActor != Pawn)
		{
			UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, -SweepResult.Normal, SweepResult, nullptr, GetOwner(), UBasicMonsterDamageType::StaticClass());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, SweepResult.ImpactPoint); 
			Destroy();
		}
	}
}


