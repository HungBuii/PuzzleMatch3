// Hungnee

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Tile.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMATCH3_API ATile : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:
	ATile();
	
	UPROPERTY(VisibleAnywhere, Category = Index, meta=(AllowPrivateAccess=true))
	int32 Index = 0;
	
	/** Set Material Gem,... */
	UFUNCTION(BlueprintNativeEvent, Category = "Gem Attributes Events")
	void SetTileMaterial(class UMaterialInstanceConstant* TileMaterial);
	virtual void SetTileMaterial_Implementation(class UMaterialInstanceConstant* TileMaterial);
	
};
