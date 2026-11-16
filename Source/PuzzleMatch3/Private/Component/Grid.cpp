// Hungnee


#include "Component/Grid.h"

#include "PaperSpriteComponent.h"
#include "Component/Tile.h"
#include "Math//UnrealMathUtility.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = false;

	TileSize.Set(28.2f, 28.2f);
}

void AGrid::InitGrid()
{
	GameTiles.Empty(GridWidth * GridHeight);
	GameTiles.AddZeroed(GameTiles.Max());
	FVector SpawnLocation;
	
	for (int32 Column = 0; Column < GridWidth; Column++) // X
	{
		for (int32 Row = 0; Row < GridHeight; Row++) // Y
		{
			int32 GridAddress;
			GetGridAddressWithOffset(0, Column, Row, GridAddress);
			SpawnLocation = GetLocationFromGridAddress(GridAddress);
			
			int32 TileID = FMath::FRandRange(0, TileLibrary.Num());
			CreateTile(TileLibrary[TileID].TileClass, TileLibrary[TileID].TileMaterial, SpawnLocation, GridAddress, TileID);
		}
	}
}

bool AGrid::GetGridAddressWithOffset(int32 InitialGridAddress, int32 XOffset, int32 YOffset,
	int32& ReturnGridAddress) const
{
	// int32 NewAxisValue;

	// Initialize to an invalid address.
	ReturnGridAddress = -1;

	// Check for going off the map in the X direction.
	// check(GridWidth > 0); // check(): "Assert Functionality" of UE C++ detect and diagnose unexpected or invalid runtime conditions during development.
	// NewAxisValue = (InitialGridAddress % GridWidth) + XOffset;
	// if (NewAxisValue != FMath::Clamp(NewAxisValue, 0, (GridWidth - 1)))
	// {
	// 	return false;
	// }

	// Check for going off the map in the Y direction.
	// NewAxisValue = (InitialGridAddress / GridWidth) + YOffset;
	// if (NewAxisValue != FMath::Clamp(NewAxisValue, 0, (GridHeight - 1)))
	// {
	// 	return false;
	// }

	ReturnGridAddress = (InitialGridAddress + XOffset + (YOffset * GridWidth)); // Gem positions will go from bottom to top.
	// ReturnGridAddress = (InitialGridAddress + YOffset + (XOffset * GridWidth)); // Gem positions will run horizontally from left to right.
	check(ReturnGridAddress >= 0);
	check(ReturnGridAddress < (GridWidth * GridHeight));
	return true;
}

FVector AGrid::GetLocationFromGridAddress(int32 GridAddress) const
{
	FVector Center = GetActorLocation(); // Grid Location in Editor
	FVector OutLocation = FVector(-(GridWidth * 0.5f) * TileSize.X + (TileSize.X * 0.5f), 
								  0.0f,
								  -(GridHeight * 0.5f) * TileSize.Y + (TileSize.Y * 0.5f));
								  // Temporary location of Gem in the bottom-left corner, outside the game board
	check(GridWidth > 0);
	OutLocation.X += TileSize.X * (float)(GridAddress % GridWidth); // update location of gem with Index
	OutLocation.Z += TileSize.Y * (float)(GridAddress / GridWidth);
	OutLocation += Center;

	return OutLocation;
}

ATile* AGrid::CreateTile(TSubclassOf<class ATile> TileToSpawn, class UMaterialInstanceConstant* TileMaterial,
	FVector SpawnLocation, int32 SpawnGridAddress, int32 TileTypeID)
{
	// If we have set something to spawn:
	if (TileToSpawn)
	{
		// Check for a valid World:
		UWorld* const World = GetWorld();
		if (World)
		{
			// Set the spawn parameters.
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			// Tiles never rotate
			FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
			// Spawn the tile.
			ATile* const NewTile = World->SpawnActor<ATile>(TileToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
			NewTile->GetRenderComponent()->SetMobility(EComponentMobility::Movable);
			NewTile->SetTileMaterial(TileMaterial);
			GameTiles[SpawnGridAddress] = NewTile;
			NewTile->Index = SpawnGridAddress; // test
			return NewTile;
		}
	}
	return nullptr;
}


