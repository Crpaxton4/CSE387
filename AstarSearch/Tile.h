// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include <vector>

class Tile : public Actor
{
public:
	friend class Grid;
	enum TileState
	{
		EDefault,
		EPath,
		EStart,
		EBase
	};
	
	Tile(class Game* game);
	
	// Mutator for the tile state
	void SetTileState(TileState state);

	// Accessor for the tile state
	TileState GetTileState() const { return mTileState; }

	// Toggle selection on and off
	void ToggleSelect();

	const Tile* GetParent() const { return mParent; }

private:

	// Vector containing a list of adjacent tiles
	std::vector<Tile*> mAdjacent;

	Tile* mParent; // Parent in the search?
	float pathCost; // g(x) path cost - actual cost from start to the tile 
	float heuristicCost; // h(x) heuristic cost - cost from the tile to the goal based on the heuristic
	float pathPlusHeuristicCost; // f(x) sum of the path cost and the heuristic cost for this tile

	// Status of the tile in the search
	bool mInOpenSet;	// Still to be examined in the search
	bool mInClosedSet;	// Examine in the search?
	bool mBlocked;		// Blocked tile
	
	// Set the texture based on the state of the tile
	void UpdateTexture();

	// Sprite component to display the image representing the state
	class SpriteComponent* mSprite;

	// State of the time
	TileState mTileState;

	// true indicates the tile is currently selected
	bool mSelected;
};
