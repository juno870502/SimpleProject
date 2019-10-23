// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "BasicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	ABasicPlayerController();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FGenericTeamId TeamID = 10;

	virtual FGenericTeamId GetGenericTeamId() const override;
};
