// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGM.h"
#include "Battle/BasicMonster.h"
#include "Battle/BasicAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include "Battle/BasicGS.h"

ABasicGM::ABasicGM()
{
	bUseSeamlessTravel = true;
}

void ABasicGM::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ABasicGM::SpawnFunction, 1.f, true);
}

void ABasicGM::WorldTravelFunc()
{
	GetWorld()->ServerTravel(TEXT("Boss"), true);
}

void ABasicGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PartyNumber++;
	MaxMonsterNumber += PartyNumber * 10;
	GetGameState<ABasicGS>();
}

void ABasicGM::SpawnFunction()
{
	//GetPlayer
	//FVector TargetVec = UNavigationSystemV1::GetRandomPointInNavigableRadius(GetWorld(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomeLocation")), 500.f);
	if (NumOfMonster < MaxMonsterNumber)
	{
		FVector SpanwLocation = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), FVector(0), 2000.f);
		FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
		ABasicMonster* Mon = GetWorld()->SpawnActor<ABasicMonster>(MonsterClass, SpanwLocation, SpawnRotation);
		NumOfMonster++;
	}
	
	//ABasicAIController* AIC = GetWorld()->SpawnActor<ABasicAIController>(MonsterAIClass);
	//AIC->Possess(Mon);
}
