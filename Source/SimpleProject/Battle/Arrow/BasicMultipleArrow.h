// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/Arrow/BasicArrow.h"
#include "BasicMultipleArrow.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API ABasicMultipleArrow : public ABasicArrow
{
	GENERATED_BODY()
	
public:
	int a;
	ABasicMultipleArrow();
};
