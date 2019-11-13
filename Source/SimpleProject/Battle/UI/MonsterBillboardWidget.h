// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterBillboardWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UMonsterBillboardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProgressBar* MonsterHPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTextBlock* DamageBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UWidgetAnimation* TextBlockAnimation;

	void ShowDamageAndHP(float NewPercent, INT32 NewDamage);
};
