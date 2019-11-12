// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBoss.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

ABasicBoss::ABasicBoss()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(200.f);
	GetCapsuleComponent()->SetCapsuleRadius(100.f);

	GetMesh()->SetRelativeLocation(FVector(1.0f, 1.0f, -200.f));
}

void ABasicBoss::FunctionOfAttack()
{
	
}
