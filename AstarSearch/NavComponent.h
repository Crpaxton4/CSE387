// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "MoveComponent.h"
#include "MathLibsConstsFuncs.h"

class NavComponent : public MoveComponent
{
public:
	// Lower update order to update first
	NavComponent(class Actor* owner, int updateOrder = 10);

	// Move the Actor. If next node is reached. Set new next and rotate Actor.
	void Update(float deltaTime) override;

	// Set the starting position and direction of the the Actor
	void StartPath(const class Tile* start);

	// Rotate the forward vector to point at the next tile
	void TurnTo(const vec2& pos);
private:

	// Next node to move towards
	const class Tile* mNextNode;
};
