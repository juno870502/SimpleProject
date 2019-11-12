// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartySlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UPartySlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UImage* Portrait;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UTextBlock* PartyName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UProgressBar* PartyHP;

	void SetPortrait();
	void SetPartyName(FText NewName);
	void SetPartyHP(float NewPercent);
};