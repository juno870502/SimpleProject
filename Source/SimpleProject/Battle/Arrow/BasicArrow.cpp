// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicArrow.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Battle/DamageType/BasicArrowDamageType.h"
#include "Battle/BasicCharacter.h"
#include "Battle/BasicPlayerController.h"
#include "Sound/SoundBase.h"
#include "Perception/AISense_Damage.h"

// Sets default values
ABasicArrow::ABasicArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Basic Components
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(40.f, 10.f, 10.f));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	HitArrowSound = CreateDefaultSubobject<USoundBase>(TEXT("HitArrowSound"));
	//HitArrowSound->bAutoActivate = false;

	// Set box collision
	Box->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	Box->SetCollisionProfileName(TEXT("PlayerATK"));
	Box->SetGenerateOverlapEvents(true);

	// Set mesh collision
	StaticMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));

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
	
	HitEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("HitEffect"));

	// Replicated on
	bReplicates = true;
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

void ABasicArrow::S2A_ChargeFunction_Implementation(int ChargeValue)
{
	ChargeFlag = ChargeValue;
	// Set Charge Shot Color
	if (ChargeFlag == 0)
	{
		Particle->SetColorParameter(TEXT("color"), FLinearColor(5.0f, 5.0f, 5.0f));
		Particle->SetRelativeScale3D(FVector(.3f));
	}
	else if (ChargeFlag == 1)
	{
		Particle->SetColorParameter(TEXT("color"), FLinearColor(7.0f, 7.0f, 0.0f));
		Particle->SetRelativeScale3D(FVector(.5f));
	}
	else if (ChargeFlag == 2)
	{
		Particle->SetColorParameter(TEXT("color"), FLinearColor(10.0f, 0.0f, 0.0f));
		Particle->SetRelativeScale3D(FVector(.7f));
	}
}

void ABasicArrow::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{	
	// Exclude Self Actor
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (Pawn)
	{
		if (OtherActor != Pawn)
		{
			float ActualDamage = BaseDamage * (ChargeFlag + 1);
			ABasicCharacter* BC = Cast<ABasicCharacter>(GetOwner());
			// Apply Damage And Play Effect 
			ABasicPlayerController* PC = Cast<ABasicPlayerController>(BC->GetController());
			if (HasAuthority())
			{
				UGameplayStatics::ApplyPointDamage(OtherActor, ActualDamage, -SweepResult.Normal, SweepResult, PC, Pawn, UBasicArrowDamageType::StaticClass());
				UAISense_Damage::ReportDamageEvent(GetWorld(), OtherActor, BC, ActualDamage, GetActorLocation(), GetActorLocation());
			}
			S2A_HitEffect(SweepResult);

			if (ChargeFlag > 0)
			{
				ChargeFlag--;
			}
			else
			{
				Destroy();
			}
		}
	}
	//UGameplayStatics::ApplyPointDamage(OtherActor, 1.0f, SweepResult.ImpactPoint, SweepResult, );
}

void ABasicArrow::S2A_HitEffect_Implementation(const FHitResult & SweepResult)
{
	// Get Mana Point
	ABasicCharacter* BC = Cast<ABasicCharacter>(GetOwner());
	BC->SetCurrentMP(BC->CurrentMP + GainManaPoint);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, SweepResult.ImpactPoint);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitArrowSound, SweepResult.ImpactPoint);
}
