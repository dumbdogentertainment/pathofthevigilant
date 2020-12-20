// Fill out your copyright notice in the Description page of Project Settings.


#include "PotV_GameBoard.h"

// Sets default values
APotV_GameBoard::APotV_GameBoard()
{
 	// Set this to false .. we don't want to ever handle tick events.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APotV_GameBoard::BeginPlay()
{
	Super::BeginPlay();

	FVector GameTileSpawnLocation;

	UWorld* const GameWorld = GetWorld();

	for(int32 Column = 0; Column < GridWidth; ++Column)
	{
		for(int32 Row = 0; Row < GridHeight; ++Row)
		{
			int32 GameBoardAddress;

			GetGameBoardAddressWithOffset(0, Column, Row, GameBoardAddress);
			GameTileSpawnLocation = GetRenderLocationFromGameBoardAddress(GameBoardAddress);

			if(GameWorld)
			{
				int32 GameTileLibraryIndex = FMath::RandRange(0, GameTileLibrary.Num() - 1);

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

				APotV_GameTile* const NewGameTile = GameWorld->SpawnActor<APotV_GameTile>(
					GameTileLibrary[GameTileLibraryIndex].GameTileClass,
					GameTileSpawnLocation,
					SpawnRotation,
					SpawnParams);
				NewGameTile->SetGameTileMaterial(GameTileLibrary[GameTileLibraryIndex].GameTileMaterial);
			}
		}
	}
}

bool APotV_GameBoard::GetGameBoardAddressWithOffset(int32 InitialGameBoardAddress, int32 XOffset, int32 YOffset, int32 &ReturnGameBoardAddress) const
{
	int32 NewAxisValue;

	ReturnGameBoardAddress = -1;

	check(GridWidth > 0);
	NewAxisValue = (InitialGameBoardAddress % GridWidth) + XOffset;
	if (NewAxisValue != FMath::Clamp(NewAxisValue, 0, (GridWidth - 1)))
	{
		return false;
	}

	NewAxisValue = (InitialGameBoardAddress / GridWidth) + YOffset;
	if (NewAxisValue != FMath::Clamp(NewAxisValue, 0, (GridHeight - 1)))
	{
		return false;
	}

	ReturnGameBoardAddress = (InitialGameBoardAddress + XOffset + (YOffset * GridWidth));
	check(ReturnGameBoardAddress >= 0);
	check(ReturnGameBoardAddress < (GridWidth * GridHeight));
	return true;
}

FVector APotV_GameBoard::GetRenderLocationFromGameBoardAddress(int32 GameBoardAddress) const
{
	FVector GameBoardCenter = GetActorLocation();
	FVector CalculatedGameTileLocation = FVector(
		-(GridWidth * 0.5f) * GameTileSize.X + (GameTileSize.X * 0.5f),
		0.0f,
		-(GridHeight * 0.5f) * GameTileSize.Y + (GameTileSize.Y * 0.5f));
	
	check(GridWidth > 0);

	CalculatedGameTileLocation.X += GameTileSize.X * (float)(GameBoardAddress % GridWidth);
	CalculatedGameTileLocation.Z += GameTileSize.Y * (float)(GameBoardAddress / GridWidth);
	CalculatedGameTileLocation += GameBoardCenter;

	return CalculatedGameTileLocation;
}