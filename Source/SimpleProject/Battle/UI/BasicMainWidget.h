// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasicMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBasicMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar* HPBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar* MPBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* GlobalText;

	virtual void NativeConstruct() override;

	void SetHP(float NewHPPercent);
	void SetMP(float NewMPPercent);
	void SetPublicMSG(int Count, int MaxCount);
};
