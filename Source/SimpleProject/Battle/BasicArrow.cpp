// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicArrow.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABasicArrow::ABasicArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(45.f, 5.f, 5.f));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	// Set box collision
	Box->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	Box->SetGenerateOverlapEvents(false);

	// Set mesh collision
	StaticMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	StaticMesh->SetCollisionProfileName(TEXT("PlayerATK"));
	StaticMesh->SetGenerateOverlapEvents(true);

	// Set projectile movement setting
	Projectile->bRotationFollowsVelocity = true;
	Projectile->ProjectileGravityScale = .1f;
	Projectile->Velocity = FVector(1.0f, 0.f, 0.f);
	Projectile->InitialSpeed = CustomInitSpeed;
}

// Called when the game starts or when spawned
void ABasicArrow::BeginPlay()
{
	Super::BeginPlay();
	
	// Set Destroy Time
	SetLifeSpan(10.f);

	// Overlap Delegate
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABasicArrow::OnOverlapBegin);
}

// Called every frame
void ABasicArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicArrow::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//UE_LOG(LogClass, Warning, TEXT("%s"), *OtherActor->GetFName());
}
