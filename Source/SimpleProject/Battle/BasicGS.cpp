// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGS.h"
#include "UnrealNetwork.h"
#include "Battle/BasicPlayerController.h"
#include "Battle/UI/BasicMainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ABasicGS::OnRep_NumOfDeath()
{
	ABasicPlayerController* PC = Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->MainWidget)
	{
		PC->MainWidget->SetPublicMSG(NumOfDeathMonsters);
	}
}

void ABasicGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasicGS, NumOfDeathMonsters);
}
