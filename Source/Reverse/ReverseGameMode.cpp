// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReverseGameMode.h"
#include "ReverseHUD.h"
#include "ReverseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AReverseGameMode::AReverseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AReverseHUD::StaticClass();
}
