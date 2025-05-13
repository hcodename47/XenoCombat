// Copyright Epic Games, Inc. All Rights Reserved.

#include "XenoCombatGameMode.h"
#include "XenoCombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AXenoCombatGameMode::AXenoCombatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
