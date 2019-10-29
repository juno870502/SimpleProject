// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Battle/BasicArrowDamageType.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Battle/BasicArrow.h"
#include "Engine/World.h"
#include "Animation/AnimMontage.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	Spring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
	Spring->SetRelativeLocationAndRotation(FVector(0.f, 50.f, 70.f), FRotator(-30.f, 0.f, 0.f));
	Spring->SetupAttachment(RootComponent);
	Spring->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Spring);

	// Collision Setting
	GetMesh()->SetCollisionProfileName(TEXT("PlayerProf"));
	GetMesh()->SetGenerateOverlapEvents(true);

	bIsAttackAvailable = true;

	// AI StimuliSource Config
	//StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
	//StimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	//StimuliSource->RegisterForSense(UAISense_Hearing::StaticClass());

	AttackMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("AttackMontage"));
	
	SetCurrentState(EBasicState::LOCO);

	CurrentHP = MaxHP;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetController())
	{
		ControlRotation = GetController()->GetControlRotation();
	}
}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABasicCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABasicCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABasicCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABasicCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ABasicCharacter::PressJump);
	PlayerInputComponent->BindAction(TEXT("Attack1"), EInputEvent::IE_Pressed, this, &ABasicCharacter::PrimaryShot);
	PlayerInputComponent->BindAction(TEXT("Attack2"), EInputEvent::IE_Pressed, this, &ABasicCharacter::RAbilityShot);

}

void ABasicCharacter::MoveForward(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.f, GetControlRotation().Yaw, 0.f))*Value);
	}
}

void ABasicCharacter::MoveRight(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, 0.f))*Value);
	}
}

void ABasicCharacter::Turn(float Value)
{
	if (Value != 0)
	{
		AddControllerYawInput(Value);
	}
}

void ABasicCharacter::LookUp(float Value)
{
	if (Value != 0)
	{
		AddControllerPitchInput(Value);
	}
}

void ABasicCharacter::PressJump()
{
	Super::Jump();
	UAISense_Hearing::ReportNoiseEvent(this->GetWorld(), GetActorLocation(), 1.f, this, 0.f, NAME_None);
	UE_LOG(LogClass, Warning, TEXT("InJump"));
}

void ABasicCharacter::PrimaryShot()
{
	MainAttackFunc(EBasicState::PrimaryShot);
}

void ABasicCharacter::RAbilityShot()
{
	MainAttackFunc(EBasicState::RAbilityShot);
}

void ABasicCharacter::QAbilityShot()
{
	MainAttackFunc(EBasicState::QAbilityShot);
}

void ABasicCharacter::MainAttackFunc(EBasicState AttackState)
{
	switch (AttackState)
	{
	case EBasicState::PrimaryShot:
	{
		//bIsAttackAvailable = false;
		FHitResult Hit;
		FVector Start = Camera->GetComponentLocation();
		FVector End = Camera->GetForwardVector() * 50000.f;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);

		SetCurrentState(EBasicState::PrimaryShot);
		PlayAnimMontage(AttackMontage, 1.f, TEXT("PrimaryShot"));

		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceQuery, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, Hit, true))
		{
			C2S_ShotArrow(Hit.Location);
			UGameplayStatics::ApplyPointDamage(Hit.GetActor(), 10.0f, this->GetActorLocation(), Hit, GetController(), this, UBasicArrowDamageType::StaticClass());
		}
		else
		{
			C2S_ShotArrow(End);
		}
	}
		break;
	case EBasicState::RAbilityShot:
		break;
	case EBasicState::QAbilityShot:
		break;
	default:
		break;
	}
}

void ABasicCharacter::C2S_ShotArrow_Implementation(const FVector & TargetLocation)
{
	//GetWorld()->SpawnActor<ABasicArrow>(Arrow_Template, GetMesh()->GetSocketTransform(TEXT("arrow_anchor")));
	FRotator LookRotator = UKismetMathLibrary::FindLookAtRotation(GetMesh()->GetSocketLocation(TEXT("arrow_anchor")), TargetLocation);
	switch (CurrentState)
	{
	case EBasicState::PrimaryShot:
		GetWorld()->SpawnActor<ABasicArrow>(Arrow_Template, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator);
		break;
	case EBasicState::RAbilityShot:
		break;
	case EBasicState::QAbilityShot:
		break;
	default:
		break;
	}
}

float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
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

void ABasicCharacter::SetCurrentState(EBasicState NewState)
{
	if (CurrentState != EBasicState::DEATH)
	{
		CurrentState = NewState;
		switch (NewState)
		{
		case EBasicState::LOCO:
			GetCharacterMovement()->MaxWalkSpeed = IdleMaxWalkSpeed;
			GetCharacterMovement()->RotationRate = IdleRotationRate;
			break;
		case EBasicState::PrimaryShot:
			GetCharacterMovement()->MaxWalkSpeed = IdleMaxWalkSpeed;
			GetCharacterMovement()->RotationRate = IdleRotationRate;
			break;
		case EBasicState::RAbilityShot:
			GetCharacterMovement()->MaxWalkSpeed = OtherMaxWalkSpeed;
			GetCharacterMovement()->RotationRate = AttackRotationRate;
			break;
		case EBasicState::QAbilityShot:
			GetCharacterMovement()->MaxWalkSpeed = OtherMaxWalkSpeed;
			GetCharacterMovement()->RotationRate = AttackRotationRate;
			break;
		case EBasicState::HIT:
			GetCharacterMovement()->MaxWalkSpeed = OtherMaxWalkSpeed;
			GetCharacterMovement()->RotationRate = IdleRotationRate;
			break;
		case EBasicState::DEATH:
			GetCharacterMovement()->MaxWalkSpeed = OtherMaxWalkSpeed;
			GetCharacterMovement()->RotationRate = IdleRotationRate;
			break;
		default:
			break;
		}
	}
	else
	{

	}
}
