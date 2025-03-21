// Copyright Epic Games, Inc. All Rights Reserved.

#include "SquidGameGameMode.h"
#include "SquidGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASquidGameGameMode::ASquidGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
