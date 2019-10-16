// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMonster.h"
#include "Components/SkeletalMeshComponent.h"
#include "Battle/BasicAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasicMonster::ABasicMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	AIControllerClass = ABasicAIController::StaticClass();

	//GetMesh()->SetCollisionProfileName(TEXT("MonsterProf"));
	//GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterProf"));

	CurrentHP = MaxHP;
}

// Called when the game starts or when spawned
void ABasicMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABasicMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	switch (DamageEvent.GetTypeID())
	{
	case FDamageEvent::ClassID:
		break;
	case FRadialDamageEvent::ClassID:
		break;
	case FPointDamageEvent::ClassID:
		CurrentHP -= Damage;
		UE_LOG(LogClass, Warning, TEXT("Current HP : %f"), CurrentHP);
		break;
	default:
		break;
	}
	return 0.0f;
}
