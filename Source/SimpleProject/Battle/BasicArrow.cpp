// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicArrow.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BasicArrowDamageType.h"

// Sets default values
ABasicArrow::ABasicArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Basic Components
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(45.f, 5.f, 5.f));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	// Set box collision
	Box->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	StaticMesh->SetCollisionProfileName(TEXT("PlayerATK"));
	Box->SetGenerateOverlapEvents(true);

	// Set mesh collision
	StaticMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	StaticMesh->SetGenerateOverlapEvents(false);

	// Set projectile movement setting
	Projectile->bRotationFollowsVelocity = true;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->Velocity = FVector(1.0f, 0.f, 0.f);
	Projectile->InitialSpeed = CustomInitSpeed;

	// Set Particle setting
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(StaticMesh, TEXT("ParticleSocket"));
	Particle->SetRelativeScale3D(FVector(.5f, .5f, .5f));
	Particle->SetColorParameter(TEXT("color"), ParticleColor);
	
}

// Called when the game starts or when spawned
void ABasicArrow::BeginPlay()
{
	Super::BeginPlay();
	
	// Set Destroy Time
	SetLifeSpan(10.f);

	// Overlap Delegate
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABasicArrow::OnOverlapBegin);
}

// Called every frame
void ABasicArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicArrow::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{	
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (Pawn)
	{
		if (OtherActor != Pawn)
		{
			APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
			UE_LOG(LogClass, Warning, TEXT("In Apply Damage : %s"), *OtherActor->GetName());
			UGameplayStatics::ApplyPointDamage(OtherActor, 1.0f, SweepResult.ImpactPoint, SweepResult, PC, Pawn, UBasicArrowDamageType::StaticClass());
			Destroy();
			
		}
		
	}
	//UGameplayStatics::ApplyPointDamage(OtherActor, 1.0f, SweepResult.ImpactPoint, SweepResult, );
}
