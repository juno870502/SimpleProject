// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayerController.h"
#include "UserWidget.h"
#include "Battle/UI/BasicMainWidget.h"
#include "Battle/BasicCharacter.h"
#include "GameFramework/SpectatorPawn.h"
#include "BasicSpectatorPawn.h"

ABasicPlayerController::ABasicPlayerController()
{
	SetGenericTeamId(10);
}

FGenericTeamId ABasicPlayerController::GetGenericTeamId() const
{
	return TeamID;
}

void ABasicPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		MainWidget = CreateWidget<UBasicMainWidget>(this, MainWidgetClass);
		if (MainWidget)
		{
			MainWidget->AddToViewport();
		}
	}
	
}

void ABasicPlayerController::SetStatusHP(float NewHPPercent)
{
	if (MainWidget)
	{
		MainWidget->SetHP(NewHPPercent);
	}
}

void ABasicPlayerController::SetStatusMP(float NewMPPercent)
{
	if (MainWidget)
	{
		MainWidget->SetMP(NewMPPercent);
	}
}

void ABasicPlayerController::GameoverSetPCtoSpectator()
{
	//
	//ABasicCharacter* BC = Cast<ABasicCharacter>(GetPawn());
	//if (BC)
	//{
	//	
	//}
	//OnUnPossess();
	//UnPossess();
	//Possess(SpawnSpectatorPawn());
	SpectatorActor = GetWorld()->SpawnActor<ABasicSpectatorPawn>();
	UnPossess();
	Possess(SpectatorActor);
}
