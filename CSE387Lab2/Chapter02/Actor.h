// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "MathLibsConstants.h"
class Actor
{
public:
	enum State
	{
		EActive, // object is updated if true
		EPaused, // ??
		EDead	 // object should be removed if true
	};

	// Constructor: 
	// Receives a pointer to the Game class object, that provides 
	// access to any required game functions
	Actor(class Game* game);

	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	const vec2 & GetPosition() const { return mPosition; }
	void SetPosition(const vec2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor's current state
	State mState = EActive;

	vec2 mPosition = v2::ZERO; // Position of the Actor
	float mScale = 1.0f;	// Size of the Actor
	float mRotation = 0.0f;	// Rotation of the Actor in radians

	// Components attached to this Actor
	std::vector<class Component*> mComponents;

	// Pointer to the Game that made this Actor
	class Game* mGame = nullptr;
};
