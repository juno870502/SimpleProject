// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMonster.h"
#include "Components/SkeletalMeshComponent.h"
#include "Battle/BasicAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Battle/DamageType/BasicMonsterDamageType.h"
#include "Battle/BasicMonProjectile.h"

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
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttackMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("AttackMontage"));
}

// Called when the game starts or when spawned
void ABasicMonster::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHP = MaxHP;
	S2A_SetCurrentState(EMonsterState::LOCO);
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
		if (DamageEvent.DamageTypeClass != UBasicMonsterDamageType::StaticClass())
		{
			CurrentHP -= Damage;
			UE_LOG(LogClass, Warning, TEXT("Monster Current HP : %f"), CurrentHP);
			if (CurrentHP <= 0)
			{
				S2A_SetCurrentState(EMonsterState::DEATH);
			}
		}
		UE_LOG(LogClass, Warning, TEXT("Hit Whatever"));
		S2A_SetCurrentState(EMonsterState::HIT);
		const FPointDamageEvent* PDE = (FPointDamageEvent*)&DamageEvent;
		LaunchCharacter(PDE->ShotDirection * 1000.f, true, true);
		break;
	}
	return Damage;
}

void ABasicMonster::S2A_SetCurrentState_Implementation(const EMonsterState & NewState)
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
	else
	{
		if (NewState == EMonsterState::SPAWN)
		{
			CurrentState = NewState;
		}
	}
}


void ABasicMonster::S2A_MomentOfAttack_Implementation()
{
	FString Str = FString::Printf(TEXT("Fire_%d"), rand()%2);

	PlayAnimMontage(AttackMontage, 1.f, *Str);
	TArray<AActor*> Ignore;
	Ignore.Add(this);
	FHitResult Hit;
	FActorSpawnParameters Param;
	Param.Owner = this;
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), GetActorForwardVector()*5000.f, ETraceTypeQuery::TraceTypeQuery4, false, Ignore, EDrawDebugTrace::ForDuration, Hit, true))
	{
		//UGameplayStatics::ApplyPointDamage(Hit.GetActor(), 1.0f, GetActorLocation(), Hit, GetController(), this, UBasicArrowDamageType::StaticClass());
		GetWorld()->SpawnActor<ABasicMonProjectile>(Projectile, GetActorLocation(), GetActorRotation(), Param);
	}
}

void ABasicMonster::InitializeValues()
{
	CurrentHP = MaxHP;
	S2A_SetCurrentState(EMonsterState::SPAWN);
}

