// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "NavComponent.h"
#include "Tile.h"

NavComponent::NavComponent(class Actor* owner, int updateOrder)
:MoveComponent(owner, updateOrder)
,mNextNode(nullptr)
{
	
}

void NavComponent::Update(float deltaTime)
{
	// Has mNextNode been set
	if (mNextNode != nullptr)
	{
		// Find distance to the next node
		vec2 diff = mOwner->GetPosition() - mNextNode->GetPosition();

		// Check if next node has been reached
		if (NearZero(glm::length(diff), 2.0f))
		{
			// Get the next node in the path
			mNextNode = mNextNode->GetParent();

			// Rotate the Actor to face the next node.
			TurnTo(mNextNode->GetPosition());
		}
	}
	
	// Call super class method to 
	MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const Tile* start)
{
	mNextNode = start->GetParent();
	TurnTo(mNextNode->GetPosition());
}

void NavComponent::TurnTo(const vec2& pos)
{
	// Vector from me to pos
	vec2 dir = pos - mOwner->GetPosition();
	// New angle is just atan2 of this dir vector
	// (Negate y because +y is down on screen)
	float angle = atan2(-dir.y, dir.x);
	mOwner->SetRotation(angle);
}
