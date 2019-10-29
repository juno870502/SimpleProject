// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayerController.h"
#include "UserWidget.h"

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
		UUserWidget* MainWidget = CreateWidget<UUserWidget>(this, MainWidgetClass);
		if (MainWidget)
		{
			MainWidget->AddToViewport();
		}
	}
}
