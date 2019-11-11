// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMainWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBasicMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPProgressBar")));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPProgressBar")));
	GlobalText = Cast<UTextBlock>(GetWidgetFromName(TEXT("PublicMessage")));
}

void UBasicMainWidget::SetHP(float NewHPPercent)
{
	if (HPBar)
	{
		HPBar->SetPercent(NewHPPercent);
	}
}

void UBasicMainWidget::SetMP(float NewMPPercent)
{
	if (MPBar)
	{
		MPBar->SetPercent(NewMPPercent);
	}
}

void UBasicMainWidget::SetPublicMSG(int Count)
{
	if (GlobalText)
	{
		GlobalText->SetText(FText::FromString(FString::Printf(TEXT("%d Monster Killed"), Count)));
	}
}


