#pragma once
#include "Component.h"
#include "SDL/SDL.h"
#include "Actor.h"
#include <iostream>

/*
 *	Class that allows the Actor to be reparented when the
 *  "p" key is pressed. Pressing p again will reparent the
 *  object to its original parent.
 */
class ReparentComponent :
	public Component
{
public:
	ReparentComponent(Actor* owner, Actor* otherParent);
	void ProcessInput(const uint8_t * keyState);
	void Update(float deltaTime);
protected:
	// Actor to set as parent when reparent is called.
	Actor* otherParent;

	// Limit how often the reparent method is called.
	float timeSinceLastReparent = 0;
};

