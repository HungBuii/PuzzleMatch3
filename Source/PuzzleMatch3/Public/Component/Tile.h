// Hungnee

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Tile.generated.h"

class AGrid;

UCLASS()
class PUZZLEMATCH3_API ATile : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:
	ATile();
	
protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleAnywhere, Category = Index, meta=(AllowPrivateAccess=true))
	int32 Index = 0;
	
	/** Set Material Gem,... */
	UFUNCTION(BlueprintNativeEvent, Category = "Gem Attributes Events")
	void SetTileMaterial(class UMaterialInstanceConstant* TileMaterial);
	virtual void SetTileMaterial_Implementation(class UMaterialInstanceConstant* TileMaterial);
	
	/** When a tile is touched. */
	UFUNCTION()
	void TilePress(ETouchIndex::Type FingerIndex, AActor* TouchedActor);
	
	/** When the user's finger moves over a tile. */
	UFUNCTION()
	void TileEnter(ETouchIndex::Type FingerIndex, AActor* TouchedActor);
	
	/** Mouse surrogate for TileEnter. */
	UFUNCTION()
	void TileEnter_Mouse(AActor* MousedOverActor);
	
	/** A glowing effect appears around the gem when the player touches it. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Special Game Events")
	void PlaySelectionEffect(bool bTurnEffectOn);
	
private:
	/** The grid that owns this tile. Currently, this is set by casting the object that spawned the tile. */
	UPROPERTY(BlueprintReadOnly, Category = Tile, meta=(AllowPrivateAccess=true))
	AGrid* Grid;
};
