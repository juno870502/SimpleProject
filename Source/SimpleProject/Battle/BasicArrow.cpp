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
}

// Called when the game starts or when spawned
void ABasicArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

