// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBossAnim.h"
#include "Boss/BasicBoss.h"

void UBasicBossAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABasicBoss* Boss = Cast<ABasicBoss>(TryGetPawnOwner());
	if (Boss)
	{
		AnimBossState = Boss->BossState;

	}
}
