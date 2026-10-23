// Hungnee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PuzzleMatch3PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMATCH3_API APuzzleMatch3PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APuzzleMatch3PlayerController();
	
protected:
	virtual void BeginPlay() override;
};
