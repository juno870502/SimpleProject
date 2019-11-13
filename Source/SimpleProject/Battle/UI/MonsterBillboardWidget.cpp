// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBillboardWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMonsterBillboardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MonsterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MonsterHPBar")));
	DamageBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));
}

void UMonsterBillboardWidget::ShowDamageAndHP(float NewPercent, INT32 NewDamage)
{
	MonsterHPBar->SetPercent(NewPercent);
	DamageBlock->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewDamage)));
	PlayAnimation(TextBlockAnimation);
}
