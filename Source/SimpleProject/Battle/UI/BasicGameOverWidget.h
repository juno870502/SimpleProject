// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasicGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API UBasicGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* Respawn;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* Spectator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UWidgetAnimation* Animation;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void RespawnButton();
	UFUNCTION()
	void SpectatorButton();
};
