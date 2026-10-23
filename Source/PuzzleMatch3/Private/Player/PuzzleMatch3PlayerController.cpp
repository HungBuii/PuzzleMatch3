// Hungnee


#include "Player/PuzzleMatch3PlayerController.h"

APuzzleMatch3PlayerController::APuzzleMatch3PlayerController()
{
}

void APuzzleMatch3PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	ClickEventKeys[0] = EKeys::LeftMouseButton;
}
