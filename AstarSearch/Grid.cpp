// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Grid.h"
#include "Tile.h"
#include "Tower.h"
#include "Enemy.h"
#include <algorithm>

Grid::Grid(class Game* game)
:Actor(game), mSelectedTile(nullptr)
{
	// 7 rows, 16 columns

	// Create seven seven vectors corresponding to the rows
	mTiles.resize(NumRows);

	// Size each of the rows to have 16 columns
	for (size_t col = 0; col < mTiles.size(); col++)
	{
		mTiles[col].resize(NumCols);
	}
	
	// Create tiles
	for (size_t row = 0; row < NumRows; row++)
	{
		for (size_t col = 0; col < NumCols; col++)
		{
			// Create a tile for this row and column position
			mTiles[row][col] = new Tile(GetGame());

			// Set the position of the tile
			mTiles[row][col]->SetPosition(vec2(TileSize/2.0f + col * TileSize, StartY + row * TileSize));
		}
	}
	
	// Set the states for the start/end tiles
	// the start and end tile positions are hard coded into the GetStartTile and GetEndTile methods
	// State of start tile is EStart
	// State of end tile is EBase
	GetStartTile()->SetTileState(Tile::EStart);
	GetEndTile()->SetTileState(Tile::EBase);
	
	// Set up adjacency lists to indicate which tile are adjacent to each other
	for (size_t row = 0; row < NumRows; row++)
	{
		for (size_t col = 0; col < NumCols; col++)
		{
			if (row > 0)
			{
				mTiles[row][col]->mAdjacent.push_back(mTiles[row-1][col]);
			}
			if (row < NumRows - 1)
			{
				mTiles[row][col]->mAdjacent.push_back(mTiles[row+1][col]);
			}
			if (col > 0)
			{
				mTiles[row][col]->mAdjacent.push_back(mTiles[row][col-1]);
			}
			if (col < NumCols - 1)
			{
				mTiles[row][col]->mAdjacent.push_back(mTiles[row][col+1]);
			}
		}
	}
	
	// Find the shortest path (in reverse) before any blocking has been added.
	// Tilese that are part of the path are given a status of EPath
	// NOTE: that the end is being passed as the start and the start as the end.
	FindPath(GetEndTile(), GetStartTile());

	// Show the tiles that are part of the pat.
	UpdatePathTiles(GetStartTile());
	
	mNextEnemy = EnemyTime;
}

void Grid::SelectTile(size_t row, size_t col)
{
	// Get the state of the selected tile
	Tile::TileState tstate = mTiles[row][col]->GetTileState();

	// Make sure the tile is not the start or the end of the path
	if (tstate != Tile::EStart && tstate != Tile::EBase)
	{

		// Deselect previous one
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}

		// Get the selected tile (again?)
		mSelectedTile = mTiles[row][col];

		// Toggle the selected tile
		mSelectedTile->ToggleSelect();
	}
}

void Grid::ProcessClick(int x, int y)
{
	// Determine "row" of the selected tile relative to starting row
	y -= static_cast<int>(StartY - TileSize / 2);

	// See if row is selectable
	if (y >= 0)
	{
		// Determine the selected row and column of the selected tile
		x /= static_cast<int>(TileSize);
		y /= static_cast<int>(TileSize);

		// If tile is in the selected rows and columns of the grid, select it.
		if (x >= 0 && x < static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows))
		{
			SelectTile(y, x);
		}
	}
}

// Implements A* pathfinding
bool Grid::FindPath(Tile* start, Tile* goal)
{
	// Reset all tiles to begin the search
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j]->pathCost = 0.0f;
			mTiles[i][j]->mInOpenSet = false;
			mTiles[i][j]->mInClosedSet = false;
		}
	}
	
	// Set of tile that have not yet been explored
	std::vector<Tile*> openSet;
	
	// Set current node to start, and add to closed set
	Tile* current = start;
	current->mInClosedSet = true;
	
	do
	{
		// Add adjacent nodes to open set
		for (Tile* neighbor : current->mAdjacent)
		{
			if (neighbor->mBlocked)
			{
				continue;
			}
			
			// Only check nodes that aren't in the closed set
			if (!neighbor->mInClosedSet)
			{
				// Check id the neighbor is not in the openset
				if (!neighbor->mInOpenSet)
				{
					// Not in the open set, so set parent
					neighbor->mParent = current;

					// Compute Euclidean distance from neighbor to the goal
					// i.e. the heuristic cost
					neighbor->heuristicCost = glm::length(neighbor->GetPosition() - goal->GetPosition());
					
					// g(x) is the parent's g plus cost of traversing edge
					neighbor->pathCost = current->pathCost + TileSize;
					neighbor->pathPlusHeuristicCost = neighbor->pathCost + neighbor->heuristicCost;
					openSet.emplace_back(neighbor);
					neighbor->mInOpenSet = true;
				}
				else // Already in the open set
				{
					// Compute g(x) cost if current becomes the parent
					float potentialNewPathCost = current->pathCost + TileSize;

					if (potentialNewPathCost < neighbor->pathCost)
					{
						// Adopt this node
						neighbor->mParent = current;
						neighbor->pathCost = potentialNewPathCost;
						// f(x) changes because g(x) changes
						neighbor->pathPlusHeuristicCost = neighbor->pathCost + neighbor->heuristicCost;
					}
				}
			}
		}
		
		// If open set is empty, all possible paths are exhausted
		if (openSet.empty())
		{
			break;
		}
		
		// Find lowest cost node in open set
		auto iter = std::min_element(openSet.begin(), openSet.end(),
									 [](Tile* a, Tile* b) {
										 return a->pathPlusHeuristicCost < b->pathPlusHeuristicCost;
									 });
		// Set to current and move from open to closed
		current = *iter;
		openSet.erase(iter);
		current->mInOpenSet = false;
		current->mInClosedSet = true;
	}
	while (current != goal);
	
	// Did we find a path?
	return (current == goal) ? true : false;

}

void Grid::UpdatePathTiles(class Tile* start)
{
	// Reset all tiles to normal (except for start/end)
	for (size_t row = 0; row < NumRows; row++)
	{
		for (size_t col = 0; col < NumCols; col++)
		{
			if (!(row == 3 && col == 0) && !(row == 3 && col == 15))
			{
				mTiles[row][col]->SetTileState(Tile::EDefault);
			}
		}
	}
	
	// Traverse the path from start to finish and set the start of all path tiles to EPath.
	Tile* t = start->mParent;
	while (t != GetEndTile())
	{
		// Set the status
		t->SetTileState(Tile::EPath);

		// Set the parent to the previous tile in the path
		t = t->mParent;
	}
}

void Grid::BuildTower()
{
	// Check if a tile is selected and not block
	if (mSelectedTile && !mSelectedTile->mBlocked)
	{
		// Set the selected tile to blocked
		mSelectedTile->mBlocked = true;

		// See if there is still a path with the path blocked
		if (FindPath(GetEndTile(), GetStartTile())==true)
		{
			// Put a tower sprite on the selected tile
			Tower* t = new Tower(GetGame());
			t->SetPosition(mSelectedTile->GetPosition());
		}
		else
		{
			// This tower would block the path, so don't allow build
			mSelectedTile->mBlocked = false;
			FindPath(GetEndTile(), GetStartTile());
		}

		// Reset the all the tiles in the path
		UpdatePathTiles(GetStartTile());
	}
}

Tile* Grid::GetStartTile()
{
	return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
	return mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
	// Is it time to spawn a new enemy?
	mNextEnemy -= deltaTime;
	if (mNextEnemy <= 0.0f)
	{
		new Enemy(GetGame());
		mNextEnemy += EnemyTime;
	}
}
