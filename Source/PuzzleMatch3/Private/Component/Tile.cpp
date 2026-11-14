// Hungnee


#include "Component/Tile.h"

#include "PaperSpriteComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	if(RootComponent)
	{
		RootComponent->SetMobility(EComponentMobility::Movable);
	}
}

void ATile::SetTileMaterial_Implementation(class UMaterialInstanceConstant* TileMaterial)
{
	GetRenderComponent()->SetMaterial(0, TileMaterial);
}
