// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayerController.h"

ABasicPlayerController::ABasicPlayerController()
{
	SetGenericTeamId(10);
}

FGenericTeamId ABasicPlayerController::GetGenericTeamId() const
{
	return TeamID;
}
