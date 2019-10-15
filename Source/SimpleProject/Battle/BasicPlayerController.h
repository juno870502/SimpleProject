// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	int a;
	ABasicPlayerController();
};
