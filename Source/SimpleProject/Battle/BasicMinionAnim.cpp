// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicMinionAnim.h"

void UBasicMinionAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABasicMonster* Mon = Cast<ABasicMonster>(TryGetPawnOwner());

	if (Mon && Mon->IsValidLowLevel())
	{
		ABPVelocity = Mon->GetVelocity().Size();
		ABPCurrentState = Mon->CurrentState;
	}
}
