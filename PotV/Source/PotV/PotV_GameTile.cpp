// Fill out your copyright notice in the Description page of Project Settings.


#include "PotV_GameTile.h"

APotV_GameTile::APotV_GameTile()
{
    // Set this to false .. we don't want to ever handle tick events.
	PrimaryActorTick.bCanEverTick = false;
}

void APotV_GameTile::SetGameTileMaterial_Implementation(UMaterialInstanceConstant* MaterialToUse)
{
    GetRenderComponent()->SetMaterial(0, MaterialToUse);
}