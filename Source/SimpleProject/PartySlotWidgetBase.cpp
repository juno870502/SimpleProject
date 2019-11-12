// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySlotWidgetBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UPartySlotWidgetBase::NativeConstruct()
{
	Portrait = Cast<UImage>(GetWidgetFromName(TEXT("PartyPortrait")));
	PartyName = Cast<UTextBlock>(GetWidgetFromName(TEXT("PartyName")));
	PartyHP = Cast<UProgressBar>(GetWidgetFromName(TEXT("PartyHP")));
}

void UPartySlotWidgetBase::SetPortrait()
{
}

void UPartySlotWidgetBase::SetPartyName(FText NewName)
{
	PartyName->SetText(NewName);
}

void UPartySlotWidgetBase::SetPartyHP(float NewPercent)
{
	PartyHP->SetPercent(NewPercent);
}
