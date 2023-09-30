// Copyright Epic Games, Inc. All Rights Reserved.

#include "RewindSystemGameMode.h"
#include "RewindSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARewindSystemGameMode::ARewindSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
