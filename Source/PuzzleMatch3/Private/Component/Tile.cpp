// Hungnee


#include "Component/Tile.h"

#include "PaperSpriteComponent.h"
#include "Component/Grid.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceConstant.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	if(RootComponent)
	{
		RootComponent->SetMobility(EComponentMobility::Movable);
	}
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	Grid = Cast<AGrid>(GetOwner());
	
	// Set our class up to handle touch events.
	OnInputTouchBegin.AddUniqueDynamic(this, &ATile::TilePress);
	OnInputTouchEnter.AddUniqueDynamic(this, &ATile::TileEnter);
}


void ATile::SetTileMaterial_Implementation(class UMaterialInstanceConstant* TileMaterial)
{
	GetRenderComponent()->SetMaterial(0, TileMaterial);
}

void ATile::TilePress(ETouchIndex::Type FingerIndex, AActor* TouchedActor)
{
	// We clicked or touched the tile.
	UE_LOG(LogTemp, Warning, TEXT("Tile was selected: %s"), *this->GetName());
	if (!UGameplayStatics::IsGamePaused(this) && Grid)
	{
		Grid->OnTileWasSelected(this);
		UE_LOG(LogTemp, Warning, TEXT("Tile was selected: %s"), *this->GetName());
	}
}

void ATile::TileEnter(ETouchIndex::Type FingerIndex, AActor* TouchedActor)
{
	// We have moved into the tile's space while we had a different tile selected. This is the same as pressing the tile directly.
	// Note that we need to make sure it's a different actual tile (i.e. not NULL) because deselecting a tile by touching it twice will then trigger the TileEnter event and re-select it.
	if (!UGameplayStatics::IsGamePaused(this) && Grid)
	{
		TilePress(FingerIndex, TouchedActor);
	}
}

void ATile::TileEnter_Mouse(AActor* MousedOverActor)
{
	// This is meant to simulate finger-swiping, so ignore if the mouse isn't clicked.
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (PC->IsInputKeyDown(EKeys::LeftMouseButton))
		{
			TileEnter(ETouchIndex::Touch1, MousedOverActor);
		}
	}
}
