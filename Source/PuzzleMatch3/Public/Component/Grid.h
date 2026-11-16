// Hungnee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class ATile;

USTRUCT(BlueprintType)
struct FTileType
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UMaterialInstanceConstant* TileMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATile> TileClass;
};

UCLASS()
class PUZZLEMATCH3_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrid();
	
	/** Initialize the tiles on the grid*/
	UFUNCTION(BlueprintCallable, Category = Initialization)
	void InitGrid();
	
	/** Get a grid address relative to another grid address. Offset between addresses is measured in tiles. */
	UFUNCTION(BlueprintCallable, Category = Tile)
	bool GetGridAddressWithOffset(int32 InitialGridAddress, int32 XOffset, int32 YOffset, int32 &ReturnGridAddress) const;
	
	/** Get the world location for a given grid address. */
	UFUNCTION(BlueprintCallable, Category = Tile)
	FVector GetLocationFromGridAddress(int32 GridAddress) const;
	
	/** Spawn a tile and associate it with a specific grid address. */
	ATile* CreateTile(TSubclassOf<class ATile> TileToSpawn, class UMaterialInstanceConstant* TileMaterial, 
		FVector SpawnLocation, int32 SpawnGridAddress, int32 TileTypeID);
		
	/** React to a tile being clicked. */
	void OnTileWasSelected(ATile* NewSelectedTile);
	
private:
	/** The size of a space on the grid. Does not include borders or spacing between tiles. */
	UPROPERTY(EditAnywhere, Category = Tile, meta=(AllowPrivateAccess=true))
	FVector2D TileSize;
	
	/** Array containing Tiles. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Grid, meta=(AllowPrivateAccess=true))
	TArray<ATile*> GameTiles;
	
	/** The width of the grid. Needed to calculate tile positions and neighbors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile, meta=(AllowPrivateAccess=true))
	int32 GridWidth = 9;
	
	/** The height of the grid. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile, meta=(AllowPrivateAccess=true))
	int32 GridHeight = 9;
	
	/** Array containing Tile types. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid, meta=(AllowPrivateAccess=true))
	TArray<FTileType> TileLibrary;
};
