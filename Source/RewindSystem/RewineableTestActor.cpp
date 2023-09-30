// Fill out your copyright notice in the Description page of Project Settings.


#include "RewineableTestActor.h"

#include "RewineableActorComponent.h"


// Sets default values
ARewineableTestActor::ARewineableTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->SetSimulatePhysics(true);

	RewineableActorComponent = CreateDefaultSubobject<URewineableActorComponent>("RewineableActorComponent");

	SetReplicates(true);
	AActor::SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ARewineableTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

