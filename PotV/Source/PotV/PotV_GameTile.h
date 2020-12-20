// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "Materials/MaterialInstanceConstant.h"

#include "PotV_GameTile.generated.h"

class UMaterialInstanceConstant;

/**
 * 
 */
UCLASS()
class POTV_API APotV_GameTile : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	APotV_GameTile();

	UFUNCTION(BlueprintNativeEvent)
	void SetGameTileMaterial(UMaterialInstanceConstant* GameTileMaterial);
	virtual void SetGameTileMaterial_Implementation(UMaterialInstanceConstant* GameTileMaterial);
	
};
