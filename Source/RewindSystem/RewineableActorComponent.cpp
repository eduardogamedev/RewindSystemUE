// Fill out your copyright notice in the Description page of Project Settings.


#include "RewineableActorComponent.h"

// Sets default values for this component's properties
URewineableActorComponent::URewineableActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void URewineableActorComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
	StartSave();
}

void URewineableActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RewindTransform(DeltaTime);
}

void URewineableActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(!TimeHandleSaveTransform.IsValid()) return;
	GetWorld()->GetTimerManager().ClearTimer(TimeHandleSaveTransform);
}

void URewineableActorComponent::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);

	if(!TimeHandleSaveTransform.IsValid()) return;
	GetWorld()->GetTimerManager().ClearTimer(TimeHandleSaveTransform);
}

void URewineableActorComponent::StartSave()
{
	TransformsSaved.Empty();
	GetWorld()->GetTimerManager().SetTimer(TimeHandleSaveTransform,this,&URewineableActorComponent::SavedTransform,TimeToSaveTransform,true);
}

void URewineableActorComponent::SavedTransform()
{
	if(TransformsSaved.Num() >= NumMaxSaves)
	{
		TransformsSaved.RemoveAt(0);
	}

	FRewindTransform TransformToSave;
	TransformToSave.Location = GetOwner()->GetActorLocation();
	TransformToSave.Rotator = GetOwner()->GetActorRotation();
	TransformsSaved.Add(TransformToSave);
}

void URewineableActorComponent::RewindTransform()
{
	if(!TimeHandleSaveTransform.IsValid()) return;
	GetWorld()->GetTimerManager().ClearTimer(TimeHandleSaveTransform);
	TimeHandleSaveTransform.Invalidate();
	
	EnablePhysics(false);
	
	Algo::Reverse(TransformsSaved);

	LastransformRewindId = 0;

	SetComponentTickEnabled(true);
}

void URewineableActorComponent::RewindTransform(float DeltaTime)
{
	if(LastransformRewindId >= TransformsSaved.Num())
	{
		StartSave();
		EnablePhysics(true);

		SetComponentTickEnabled(false);

		InterpolationAlpha  = 0.0f;
		return;
	}
	
	InterpolationAlpha += RewindSpeed * DeltaTime;
	InterpolationAlpha = FMath::Clamp(InterpolationAlpha, 0.0f, 1.0f);

	const FRewindTransform TransformSaved = TransformsSaved[LastransformRewindId];
	
	const FVector EndLocation = TransformSaved.Location;
	GetOwner()->SetActorLocation(LerpActorLocation(EndLocation));

	const FRotator EndRotation = TransformSaved.Rotator;
	GetOwner()->SetActorRotation(LerpActorRotation(EndRotation));

	if(IsInDistance(EndLocation))
	{
		LastransformRewindId++;
	}
}

FVector URewineableActorComponent::LerpActorLocation(const FVector& EndLocation) const
{
	const FVector ActualLocation = GetOwner()->GetActorLocation();
	return FMath::Lerp(ActualLocation,EndLocation,InterpolationAlpha);
}

FRotator URewineableActorComponent::LerpActorRotation(const FRotator& EndRotation) const
{
	const FRotator ActoalRotation = GetOwner()->GetActorRotation();
	return FRotator(FQuat::Slerp(FQuat(ActoalRotation), FQuat(EndRotation), InterpolationAlpha));
}

bool URewineableActorComponent::IsInDistance(const FVector& EndLocation) const
{
	const FVector ActualLocation = GetOwner()->GetActorLocation();
	float Dist = FVector::Dist(ActualLocation,EndLocation);
	return Dist <= 0.05f;
}

void URewineableActorComponent::EnablePhysics(bool bEnable) const
{
	UPrimitiveComponent* PrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if(!IsValid(PrimitiveComponent)) return;
	PrimitiveComponent->SetSimulatePhysics(bEnable);
	PrimitiveComponent->SetCollisionEnabled((bEnable)?ECollisionEnabled::QueryAndPhysics:ECollisionEnabled::NoCollision);
}

