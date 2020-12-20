// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotV_GameTile.h"

#include "PotV_GameBoard.generated.h"

class APotV_GameTile;
class UMaterialInstanceConstant;

USTRUCT(BlueprintType)
struct FGameTileType
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APotV_GameTile> GameTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceConstant* GameTileMaterial = nullptr;
};

UCLASS()
class POTV_API APotV_GameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotV_GameBoard();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameTileType> GameTileLibrary;

	UPROPERTY(EditAnywhere, Category = GameTile)
	FVector2D GameTileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameBoard)
	int32 GridWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameBoard)
	int32 GridHeight;

	UFUNCTION(BlueprintCallable, Category = GameTile)
	bool GetGameBoardAddressWithOffset(int32 InitialGameBoardAddress, int32 XOffset, int32 YOffset, int32 &ReturnGameBoardAddress) const;

	UFUNCTION(BlueprintCallable, Category = GameTile)
	FVector GetRenderLocationFromGameBoardAddress(int32 GameBoardAddress) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
