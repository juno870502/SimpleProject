// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackAvailable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Battle/BasicCharacter.h"

void UPlayerAttackAvailable::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABasicCharacter* BC = Cast<ABasicCharacter>(MeshComp->GetOwner());
	if (BC)
	{
		BC->SetAttackAvailability(true);
		BC->SetCurrentState(EBasicState::LOCO);
	}
}
