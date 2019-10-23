// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BasicGM.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABasicGM();
	virtual void BeginPlay() override;
};
