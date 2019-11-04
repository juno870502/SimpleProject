// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTravelActor.h"
#include "Battle/BasicCharacter.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Battle/BasicGM.h"

// Sets default values
AWorldTravelActor::AWorldTravelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(180.f);
	RootComponent = Sphere;

	
}

// Called when the game starts or when spawned
void AWorldTravelActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AWorldTravelActor::OverlapToTravelWorld);
}

// Called every frame
void AWorldTravelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldTravelActor::OverlapToTravelWorld(AActor * OverlappedActor, AActor * OtherActor)
{
	ABasicCharacter* BC = Cast<ABasicCharacter>(OtherActor);
	if (BC)
	{
		ABasicGM* GM = Cast<ABasicGM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM)
		{
			GM->WorldTravelFunc();
		}
	}
}

