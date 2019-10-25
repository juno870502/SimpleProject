// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharAnimInstance.h"
#include "Battle/BasicCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBasicCharAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABasicCharacter* Char = Cast<ABasicCharacter>(TryGetPawnOwner());
	if (Char && Char->IsValidLowLevel())
	{
		ABPVelocity = Char->GetVelocity().Size();
		ABPCurrentState = Char->CurrentState;
		ABPAngle = CalculateDirection(Char->GetCharacterMovement()->Velocity,
			Char->GetActorRotation());
	}
}
