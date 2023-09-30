// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RewindActorComponent.generated.h"


class URewineableActorComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REWINDSYSTEM_API URewindActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URewindActorComponent();

	UFUNCTION(Server,Reliable)
	void Server_StartRewind();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<URewineableActorComponent*> RewinablesActors;
};
