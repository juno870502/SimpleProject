// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicArrowRainSpawner.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

void ABasicArrowRainSpawner::BeginPlay()
{
	Super::BeginPlay();
	//GetWorldTimerManager().SetTimer(InputTimerHandle, this, &ABasicCharacter::InputTimerFunc, ResetATKTime, false, ResetATKTime);
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ABasicArrowRainSpawner::SpawnFunction, 1.f, false, 1.f);
	UE_LOG(LogClass, Warning, TEXT("In BeginPlay Spawner"));

	// Can't Conllision
	StaticMesh->SetGenerateOverlapEvents(false);
	Box->SetGenerateOverlapEvents(false);
}

void ABasicArrowRainSpawner::SpawnFunction()
{
	//GetWorld()->SpawnActor<ABasicArrow>(PrimaryArrow, GetMesh()->GetSocketLocation(TEXT("arrow_anchor")) + GetMesh()->GetSocketLocation(TEXT("arrow_anchor")).ForwardVector * 20.f, LookRotator);
	UE_LOG(LogClass, Warning, TEXT("In Spawn Func"));
	GetWorld()->SpawnActor<AActor>(ArrowRain, GetActorLocation(), GetActorRotation().Add(-45.f, 0.f, 0.f));
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	Destroy();
}
