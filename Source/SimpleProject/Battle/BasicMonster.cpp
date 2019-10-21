// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMonster.h"
#include "Components/SkeletalMeshComponent.h"
#include "Battle/BasicAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Battle/BasicArrowDamageType.h"

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

	// Monster Rotation Setup
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

// Called when the game starts or when spawned
void ABasicMonster::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHP = MaxHP;
	SetCurrentState(EMonsterState::SPAWN);
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
		if (CurrentHP <= 0)
		{
			SetCurrentState(EMonsterState::DEATH);
		}
		SetCurrentState(EMonsterState::HIT);
		break;
	default:
		break;
	}
	return 0.0f;
}

void ABasicMonster::SetCurrentState(EMonsterState NewState)
{
	if (CurrentState != EMonsterState::DEATH)
	{
		CurrentState = NewState;
		switch (NewState)
		{
		case EMonsterState::SPAWN:
			GetCharacterMovement()->MaxWalkSpeed = 0.f;
			break;
		case EMonsterState::LOCO:
			GetCharacterMovement()->MaxWalkSpeed = 200.f;
			break;
		case EMonsterState::CHASE:
			GetCharacterMovement()->MaxWalkSpeed = 400.f;
			break;
		case EMonsterState::ATTACK:
			GetCharacterMovement()->MaxWalkSpeed = 0.f;
			break;
		case EMonsterState::HIT:
			GetCharacterMovement()->MaxWalkSpeed = 0.f;
			break;
		case EMonsterState::DEATH:
			GetCharacterMovement()->MaxWalkSpeed = 0.f;
			break;
		default:
			break;
		}
	}
}

void ABasicMonster::MomentOfAttack()
{
	TArray<AActor*> Ignore;
	FHitResult Hit;
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), GetActorForwardVector()*5000.f, ETraceTypeQuery::TraceTypeQuery4, false, Ignore, EDrawDebugTrace::ForDuration, Hit, true))
	{
		UGameplayStatics::ApplyPointDamage(Hit.GetActor(), 1.0f, GetActorLocation(), Hit, GetController(), this, UBasicArrowDamageType::StaticClass());
	}
}
