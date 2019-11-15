// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGameOverWidget.h"
#include "Components/Button.h"
#include "WidgetAnimation.h"

void UBasicGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Respawn = Cast<UButton>(GetWidgetFromName(TEXT("Respawn")));
	Spectator = Cast<UButton>(GetWidgetFromName(TEXT("Spectator")));
	Animation = CreateDefaultSubobject<UWidgetAnimation>(TEXT("Animation"));

	Respawn->OnClicked.AddDynamic(this, &UBasicGameOverWidget::RespawnButton);
	Spectator->OnClicked.AddDynamic(this, &UBasicGameOverWidget::SpectatorButton);
}

void UBasicGameOverWidget::RespawnButton()
{
}

void UBasicGameOverWidget::SpectatorButton()
{
}
