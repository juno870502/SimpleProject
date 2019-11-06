// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMainWidget.h"
#include "Components/ProgressBar.h"

void UBasicMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPProgressBar")));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPProgressBar")));
}

void UBasicMainWidget::SetHP(float NewHPPercent)
{
	HPBar->SetPercent(NewHPPercent);
}

void UBasicMainWidget::SetMP(float NewMPPercent)
{
	MPBar->SetPercent(NewMPPercent);
}


