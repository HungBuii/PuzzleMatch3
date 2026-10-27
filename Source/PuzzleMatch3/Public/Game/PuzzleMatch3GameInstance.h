// Hungnee

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleMatch3GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMATCH3_API UPuzzleMatch3GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPuzzleMatch3GameInstance();
	
	// Called by the game at startup.
	void Init() override;
	
	// Called by the game as it shuts down.
	void Shutdown() override;
	
	// Internal function to bind to viewport resizing delegate
	void OnViewportResize_Internal(FViewport* Viewport, uint32 ID);
	
	// Blueprint event to use to respond to viewport resizing, since FViewport* is not a valid Blueprint pin type
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")	
	void OnViewportResize();
	
private:
	FDelegateHandle ViewportHandle;
};
