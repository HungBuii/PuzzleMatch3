// Hungnee


#include "Game/PuzzleMatch3GameInstance.h"

UPuzzleMatch3GameInstance::UPuzzleMatch3GameInstance()
{
}

void UPuzzleMatch3GameInstance::Init()
{
	Super::Init();
	
	ViewportHandle = FViewport::ViewportResizedEvent.AddUObject(this, &UPuzzleMatch3GameInstance::OnViewportResize_Internal);
}

void UPuzzleMatch3GameInstance::Shutdown()
{
	Super::Shutdown();
	
	FViewport::ViewportResizedEvent.Remove(ViewportHandle);
}

void UPuzzleMatch3GameInstance::OnViewportResize_Internal(FViewport* Viewport, uint32 ID)
{
	OnViewportResize();
}
