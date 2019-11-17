// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Engine/World.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Animation/AnimMontage.h"
#include "TimerManager.h"
#include "Battle/Arrow/BasicArrow.h"
#include "Battle/BasicMonster.h"
#include "Battle/DamageType/BasicArrowDamageType.h"
#include "Battle/BasicPlayerController.h"
#include "DamageType/BasicArrowRainDamageType.h"



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

	// Sound Setting
	ShotArrowSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotArrowSound"));
	ShotArrowSound->bAutoActivate = false;

	// Scene Capture
	MinimapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Minimap"));
	MinimapCapture->SetupAttachment(RootComponent);
	MinimapCapture->SetWorldLocationAndRotation(FVector(0.f, 0.f, 3000.f), FRotator(-90.f, 0.f, 0.f));
	MinimapCapture->ProjectionType = ECameraProjectionMode::Orthographic;
	MinimapCapture->OrthoWidth = 4096.f;


	// Set Status
	AttackMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("AttackMontage"));
	SetCurrentState(EBasicState::LOCO);
	CurrentHP = MaxHP;
	CurrentMP = 0.f;
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
	PlayerInputComponent->BindAction(TEXT("Attack1"), EInputEvent::IE_Pressed, this, &ABasicCharacter::LeftClick);
	PlayerInputComponent->BindAction(TEXT("Attack1"), EInputEvent::IE_Released, this, &ABasicCharacter::LeftRelease);
	PlayerInputComponent->BindAction(TEXT("Attack2"), EInputEvent::IE_Pressed, this, &ABasicCharacter::RightClick);

}

void ABasicCharacter::SetCurrentMP(float NewMP)
{
	CurrentMP = UKismetMathLibrary::ClampAngle(NewMP, 0.f, 100.f);
	ABasicPlayerController* BPC = Cast<ABasicPlayerController>(GetController());
	if (BPC)
	{
		BPC->SetStatusMP(CurrentMP / MaxMP);
	}
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

void ABasicCharacter::LeftClick()
{
	if (InputTimerHandle.IsValid())
	{
		InputFlag += 1;
	}
	else
	{
		GetWorldTimerManager().SetTimer(InputTimerHandle, this, &ABasicCharacter::InputTimerFunc, ResetATKTime, false, ResetATKTime);
		InputFlag += 1;
	}
	GetWorldTimerManager().SetTimer(ChargeTimerHandle, this, &ABasicCharacter::ChargeTimerFunc, 0.5f, true, .5f);
}

void ABasicCharacter::LeftRelease()
{
	if (ChargeFlag > 0)
	{
		InputFlag = 10;
		GetWorldTimerManager().SetTimer(InputTimerHandle, this, &ABasicCharacter::InputTimerFunc, ResetATKTime, false, ResetATKTime);
	}
	GetWorldTimerManager().ClearTimer(ChargeTimerHandle);
}

void ABasicCharacter::RightClick()
{
	if (InputTimerHandle.IsValid())
	{
		InputFlag += 2;
	}
	else
	{
		GetWorldTimerManager().SetTimer(InputTimerHandle, this, &ABasicCharacter::InputTimerFunc, ResetATKTime, false, ResetATKTime);
		InputFlag += 2;
	}
}

void ABasicCharacter::InputTimerFunc()
{
	GetWorldTimerManager().ClearTimer(InputTimerHandle);
	if (bIsAttackAvailable == true)
	{
		ABasicPlayerController* PC = Cast<ABasicPlayerController>(GetController());
		int SizeX;
		int SizeY;
		FVector CrosshairLocation;
		FVector CrosshairDirection;
		FVector NewTargetVector;

		FHitResult Hit;
		PC->GetViewportSize(SizeX, SizeY);
		PC->DeprojectScreenPositionToWorld(SizeX / 2.0, SizeY / 2.0, CrosshairLocation, CrosshairDirection);
		FVector Start = Camera->GetComponentLocation();
		FVector End = Camera->GetComponentLocation() + CrosshairDirection * 5000.f;
		//bIsAttackAvailable = false;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceQuery, false, ActorsToIgnore, EDrawDebugTrace::None, Hit, true))
		{
			NewTargetVector = Hit.Location;
		}
		else
		{
			NewTargetVector = End;
		}

		switch (InputFlag)
		{
		case 1:
			C2S_MainAttackFunc(EBasicState::PrimaryShot, NewTargetVector);
			UE_LOG(LogClass, Warning, TEXT("PrimaryShot Call"));
			break;
		case 2:
			C2S_MainAttackFunc(EBasicState::RAbilityShot, NewTargetVector);
			UE_LOG(LogClass, Warning, TEXT("RAbilityShot Call"));
			break;
		case 3:
			C2S_MainAttackFunc(EBasicState::QAbilityShot, NewTargetVector);
			UE_LOG(LogClass, Warning, TEXT("QAbilityShot Call"));
			break;
		case 10:
			C2S_MainAttackFunc(EBasicState::PrimaryShot, NewTargetVector, ChargeFlag);
			UE_LOG(LogClass, Warning, TEXT("PrimaryShot Call"));
			break;
		default:
			UE_LOG(LogClass, Warning, TEXT("Error Shot Call"));
			break;
		}
	}
	InputFlag = 0;
	ChargeFlag = 0;
}

void ABasicCharacter::ChargeTimerFunc()
{
	if (ChargeFlag < 2)
	{
		UE_LOG(LogClass, Warning, TEXT("Charge Func"));
		ChargeFlag++;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ChargeTimerHandle);
	}
}

void ABasicCharacter::C2S_MainAttackFunc_Implementation(const EBasicState & AttackState, FVector TargetVector, int ChargeParam)
{
	ChargeFlag = ChargeParam;
	S2A_SubAttackFunc(AttackState, TargetVector);
	switch (AttackState)
	{
	case EBasicState::PrimaryShot:
		ShotArrow(TargetVector);
		break;
	case EBasicState::RAbilityShot:
		if (CurrentMP >= RAbilityConsumption)
		{
			ShotArrow(TargetVector);
			// Mana Cost
			SetCurrentMP(CurrentMP - RAbilityConsumption);
		}
		break;
	case EBasicState::QAbilityShot:
		if (CurrentMP >= QAbilityConsumption)
		{
			FVector Normal45 = UKismetMathLibrary::Normal(GetActorForwardVector() + GetActorUpVector()) * 50000.f;
			ShotArrow(Normal45);
			// Mana Cost
			SetCurrentMP(CurrentMP - QAbilityConsumption);
		}
		break;
	}
}

void ABasicCharacter::S2A_SubAttackFunc_Implementation(const EBasicState& AttackState, FVector TargetVector)
{
	switch (AttackState)
	{
	case EBasicState::PrimaryShot:
	{
		// Set Shot Moment
		SetCurrentState(EBasicState::PrimaryShot);
		PlayAnimMontage(AttackMontage, 1.f, TEXT("PrimaryShot"));
		ShotArrowSound->Play();
		bIsAttackAvailable = false;
	}
		break;
	case EBasicState::RAbilityShot:
	{
		if (CurrentMP >= RAbilityConsumption)
		{
			// Set Shot Moment
			SetCurrentState(EBasicState::RAbilityShot);
			PlayAnimMontage(AttackMontage, .7f, TEXT("RAbilityShot"));
			ShotArrowSound->Play();
			bIsAttackAvailable = false;
		}
	}
		break;
	case EBasicState::QAbilityShot:
	{
		if (CurrentMP >= QAbilityConsumption)
		{
			// Set Shot Moment
			SetCurrentState(EBasicState::QAbilityShot);
			PlayAnimMontage(AttackMontage, 1.f, TEXT("QAbilityShot"));
			ShotArrowSound->Play();
			bIsAttackAvailable = false;
		}
	}
		break;
	default:
		break;
	}
}

void ABasicCharacter::ShotArrow(const FVector & TargetLocation)
{
	if (HasAuthority())
	{
		//GetWorld()->SpawnActor<ABasicArrow>(Arrow_Template, GetMesh()->GetSocketTransform(TEXT("arrow_anchor")));
		FRotator LookRotator = UKismetMathLibrary::FindLookAtRotation(GetMesh()->GetSocketLocation(TEXT("arrow_anchor")), TargetLocation);
		FActorSpawnParameters Param;
		Param.Owner = this;
		ABasicArrow* Arrow;
		switch (CurrentState)
		{
		case EBasicState::PrimaryShot:
			Arrow = GetWorld()->SpawnActor<ABasicArrow>(PrimaryArrow, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator, Param);
			if (Arrow)
			{
				Arrow->S2A_ChargeFunction(ChargeFlag);
			}
			break;
		case EBasicState::RAbilityShot:
			GetWorld()->SpawnActor<ABasicArrow>(RAbilityArrow, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator.Add(0.f, -30.f, 0.f), Param);
			GetWorld()->SpawnActor<ABasicArrow>(RAbilityArrow, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator.Add(0.f, 15.f, 0.f), Param);
			GetWorld()->SpawnActor<ABasicArrow>(RAbilityArrow, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator.Add(0.f, 15.f, 0.f), Param);
			GetWorld()->SpawnActor<ABasicArrow>(RAbilityArrow, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator.Add(0.f, 15.f, 0.f), Param);
			GetWorld()->SpawnActor<ABasicArrow>(RAbilityArrow, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator.Add(0.f, 15.f, 0.f), Param);
			break;
		case EBasicState::QAbilityShot:
			Arrow = GetWorld()->SpawnActor<ABasicArrow>(QAbilityArrow, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator, Param);
			Arrow->CustomInitSpeed = 500.f;
			break;

		}
	}
}

void ABasicCharacter::SetAttackAvailability(bool NewAvailable)
{
	bIsAttackAvailable = NewAvailable;
}

float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	ABasicCharacter* BC = Cast<ABasicCharacter>(DamageCauser);
	ABasicPlayerController* BPC = Cast<ABasicPlayerController>(GetController());

	switch (DamageEvent.GetTypeID())
	{
	case FDamageEvent::ClassID:
		CurrentHP -= Damage;
		if (BPC)
		{
			BPC->SetStatusHP(CurrentHP / MaxHP);
		}
		UE_LOG(LogClass, Warning, TEXT("In Normal Damage"));
		break;
	case FRadialDamageEvent::ClassID:
		if (DamageEvent.DamageTypeClass != UBasicArrowRainDamageType::StaticClass())
		{
			CurrentHP -= Damage;
			if (BPC)
			{
				BPC->SetStatusHP(CurrentHP / MaxHP);
			}
		}
		break;
	case FPointDamageEvent::ClassID:
		// if Monster Attack Hit...
		if (!BC)
		{
			CurrentHP -= Damage;
			
			if (BPC)
			{
				BPC->SetStatusHP(CurrentHP / MaxHP);
			}
			//UE_LOG(LogClass, Warning, TEXT("Damage Causer : %s, Current HP : %f"), *DamageCauser->GetName(), CurrentHP);
		}
		//S2A_SetCurrentHP(CurrentHP);
		//UE_LOG(LogClass, Warning, TEXT("Damage Instigator : %s"), *EventInstigator->GetName());
		SetCurrentState(EBasicState::HIT);
		const FPointDamageEvent* PDE = (FPointDamageEvent*)&DamageEvent;
		LaunchCharacter(PDE->ShotDirection * 100.f, true, false);
		break;
	}

	// Dead Function
	if (CurrentHP <= 0)
	{
		S2A_DeadFuntion();
	}

	return 0.0f;
}

void ABasicCharacter::S2A_DeadFuntion_Implementation()
{
	SetCurrentState(EBasicState::DEATH);
	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	ABasicPlayerController* BPC = Cast<ABasicPlayerController>(GetController());
	if (BPC)
	{
		BPC->GameoverSetPCtoSpectator();
	}
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
