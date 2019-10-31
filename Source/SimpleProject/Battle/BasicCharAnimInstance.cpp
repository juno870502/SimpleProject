// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharAnimInstance.h"
#include "Battle/BasicCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BasicPlayerController.h"

void UBasicCharAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABasicCharacter* Char = Cast<ABasicCharacter>(TryGetPawnOwner());
	if (Char && Char->IsValidLowLevel())
	{
		ABPVelocity = Char->GetCharacterMovement()->Velocity.Size2D();
		ABPCurrentState = Char->CurrentState;
		ABPAngle = CalculateDirection(Char->GetCharacterMovement()->Velocity, Char->GetActorRotation());
		AimOffsetPitch = Char->GetBaseAimRotation().Pitch;
		
		
		FRotator TargetRotator = UKismetMathLibrary::NormalizedDeltaRotator(Char->GetBaseAimRotation(), Char->GetActorRotation());
		AimOffsetPitch = UKismetMathLibrary::Clamp(TargetRotator.Pitch, -90, 90);
		AimOffsetYaw = UKismetMathLibrary::Clamp(TargetRotator.Yaw, -90, 90);

		ControlRotationYaw = Char->GetControlRotation().Yaw;

	}
}
