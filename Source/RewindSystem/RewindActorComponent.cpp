// Fill out your copyright notice in the Description page of Project Settings.


#include "RewindActorComponent.h"

#include "EngineUtils.h"
#include "RewineableActorComponent.h"
#include "RewineableTestActor.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
URewindActorComponent::URewindActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void URewindActorComponent::Server_StartRewind_Implementation()
{
	for (auto RewineableActor : RewinablesActors)
	{
		RewineableActor->RewindTransform();
	}
}

// Called when the game starts
void URewindActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> RewineablesActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARewineableTestActor::StaticClass(), RewineablesActors);
	for (auto RewineableActor : RewineablesActors)
	{
		URewineableActorComponent* RewineableActorComponent=  RewineableActor->FindComponentByClass<URewineableActorComponent>();
		if(!IsValid(RewineableActorComponent)) return;

		RewinablesActors.Add(RewineableActorComponent);
	}
}



