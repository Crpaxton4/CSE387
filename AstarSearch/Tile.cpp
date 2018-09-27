// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(class Game* game)
:Actor(game)
,mParent(nullptr)
,pathPlusHeuristicCost(0.0f)
,pathCost(0.0f)
,heuristicCost(0.0f)
,mBlocked(false)
,mSprite(nullptr)
,mTileState(EDefault)
,mSelected(false)
{
	mSprite = new SpriteComponent(this);
	UpdateTexture();
}

void Tile::SetTileState(TileState state)
{
	mTileState = state;

	// Set texture to indicate selection status
	// Based on the state of the tile
	UpdateTexture();
}

void Tile::ToggleSelect()
{
	// Toggle selection on and off
	mSelected = !mSelected;

	// Update texture to indicate selection status
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	std::string text;
	switch (mTileState)
	{
		case EStart:
			text = "Assets/TileTan.png";
			break;
		case EBase:
			text = "Assets/TileGreen.png";
			break;
		case EPath:
			if (mSelected)
				text = "Assets/TileGreySelected.png";
			else
				text = "Assets/TileGrey.png";
			break;
		case EDefault:
		default:
			if (mSelected)
				text = "Assets/TileBrownSelected.png";
			else
				text = "Assets/TileBrown.png";
			break;
	}
	mSprite->SetTexture(GetGame()->GetTexture(text));
}
