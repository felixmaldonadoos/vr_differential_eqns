// Copyright Epic Games, Inc. All Rights Reserved.


#include "vr_differential_eqnsPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "vr_differential_eqnsCameraManager.h"

Avr_differential_eqnsPlayerController::Avr_differential_eqnsPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = Avr_differential_eqnsCameraManager::StaticClass();
}

void Avr_differential_eqnsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
