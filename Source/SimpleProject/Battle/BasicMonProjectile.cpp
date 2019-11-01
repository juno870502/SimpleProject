// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMonProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABasicMonProjectile::ABasicMonProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Basic Components
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	// Set Sphere
	Sphere->SetSphereRadius(50.f);
	Sphere->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	Sphere->SetCollisionProfileName(TEXT("MonATK"));
	Sphere->SetGenerateOverlapEvents(true);

	// Set mesh collision
	StaticMesh->SetRelativeScale3D(FVector(.3f));
	StaticMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	StaticMesh->SetGenerateOverlapEvents(false);

	// Set projectile movement setting
	Projectile->bRotationFollowsVelocity = true;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->Velocity = FVector(1.0f, 0.f, 0.f);
	Projectile->InitialSpeed = CustomInitSpeed;
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
	UE_LOG(LogClass, Warning, TEXT("Enemy Ball Hit : %s"), *OtherActor->GetName());
}

