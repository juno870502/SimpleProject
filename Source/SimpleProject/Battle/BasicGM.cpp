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
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ABasicGM::SpawnFunction, 5.f, true);
}

void ABasicGM::WorldTravelFunc()
{
	GetWorld()->ServerTravel(TEXT("Boss"), true);
}

void ABasicGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PartyNumber++;
	MaxMonsterNumber += PartyNumber * MonsterPerPlayer;
	ABasicGS* GS = GetGameState<ABasicGS>();
	GS->GoalOfKilledMonsters = MaxMonsterNumber;
	
}

void ABasicGM::SpawnFunction()
{
	//GetPlayer
	//FVector TargetVec = UNavigationSystemV1::GetRandomPointInNavigableRadius(GetWorld(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomeLocation")), 500.f);
	TArray<AActor*> FieldMonsters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicMonster::StaticClass(), FieldMonsters);
	NumOfMonster = FieldMonsters.Num();
	if (NumOfMonster < MaxMonsterNumber)
	{
		FNavLocation SpanwLocation;
		Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem())->GetRandomReachablePointInRadius(FVector(0), 2000.f, SpanwLocation);
		FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
		ABasicMonster* Mon = GetWorld()->SpawnActor<ABasicMonster>(MonsterClass, SpanwLocation, SpawnRotation);
	}
	
	//ABasicAIController* AIC = GetWorld()->SpawnActor<ABasicAIController>(MonsterAIClass);
	//AIC->Possess(Mon);
}
