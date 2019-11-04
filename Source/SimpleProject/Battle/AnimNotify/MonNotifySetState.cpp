// Fill out your copyright notice in the Description page of Project Settings.


#include "MonNotifySetState.h"
#include "Battle/BasicMonster.h"
#include "Components/SkeletalMeshComponent.h"

void UMonNotifySetState::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ABasicMonster* Mon = Cast<ABasicMonster>(MeshComp->GetOwner());
	if (Mon)
	{
		Mon->SetCurrentState(NewState);
	}
}
