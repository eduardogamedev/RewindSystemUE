// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RewineableActorComponent.generated.h"

USTRUCT(BlueprintType)
struct FRewindTransform
{
	GENERATED_BODY()
	
	UPROPERTY()
	FVector Location;
	
	UPROPERTY()
	FRotator Rotator;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REWINDSYSTEM_API URewineableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URewineableActorComponent();

	void RewindTransform();

protected:

	UPROPERTY(EditDefaultsOnly,Category=Settings)
	float TimeToSaveTransform = 0.15f;

	UPROPERTY(EditDefaultsOnly,Category=Settings)
	int32 NumMaxSaves = 1250;

	UPROPERTY(EditDefaultsOnly,Category=Settings)
	float RewindSpeed = 25.0f;
	
	UPROPERTY()
	TArray<FRewindTransform> TransformsSaved;

	FTimerHandle TimeHandleSaveTransform;

	int32 LastransformRewindId = 0;
	float InterpolationAlpha = 0.0f;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void DestroyComponent(bool bPromoteChildren) override;

	void StartSave();
	void SavedTransform();
	void RewindTransform(float DeltaTime);
	FVector LerpActorLocation(const FVector& EndLocation) const;
	FRotator LerpActorRotation(const FRotator& EndRotation) const;
	bool IsInDistance(const FVector& EndLocation) const;

private:
	void EnablePhysics(bool bEnable) const;
};
