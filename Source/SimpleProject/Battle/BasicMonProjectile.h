// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicMonProjectile.generated.h"

UCLASS()
class SIMPLEPROJECT_API ABasicMonProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicMonProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USphereComponent* Sphere;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProjectileMovementComponent* Projectile;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UParticleSystemComponent* BeamParticle;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor ParticleColor = FLinearColor(5.f, 0.f, 0.f);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float CustomInitSpeed = 3000.f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UParticleSystem* HitEffect;
};
