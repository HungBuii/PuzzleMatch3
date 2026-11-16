// Hungnee


#include "Player/PuzzleMatch3PlayerController.h"

APuzzleMatch3PlayerController::APuzzleMatch3PlayerController()
{
	// We want the mouse cursor to show immediately on startup, without having to click in the window.
	bShowMouseCursor = true;

	// We need click/touch events to interact with our tiles.
	bEnableTouchEvents = bEnableClickEvents = true;
	bEnableTouchOverEvents = bEnableMouseOverEvents = true;
}

void APuzzleMatch3PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}
