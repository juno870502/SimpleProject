// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicNotifySetState.h"
#include "Components/SkeletalMeshComponent.h"
#include "Battle/BasicCharacter.h"

void UBasicNotifySetState::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ABasicCharacter* Char = Cast<ABasicCharacter>(MeshComp->GetOwner());
	if (Char)
	{
		Char->SetCurrentState(NewState);
	}
}
