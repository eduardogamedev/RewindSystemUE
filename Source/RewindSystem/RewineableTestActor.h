// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RewineableTestActor.generated.h"

class URewineableActorComponent;
class UStaticMeshComponent;

UCLASS()
class REWINDSYSTEM_API ARewineableTestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARewineableTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category=Config)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly,Category=Config)
	URewineableActorComponent* RewineableActorComponent;
};
