// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGM.h"
#include "Battle/BasicMonster.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ABasicGM::ABasicGM()
{
	bUseSeamlessTravel = true;
}

void ABasicGM::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicGM::WorldTravelFunc()
{
	GetWorld()->ServerTravel(TEXT("Boss"), true);
}
