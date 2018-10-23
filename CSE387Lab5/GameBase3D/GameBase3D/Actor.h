// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
//#include "Math.h"
#include "MathLibsConstsFuncs.h"
#include <cstdint>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const uint8_t* keyState);
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const uint8_t* keyState);

	// Getters/setters
	const vec3& GetPosition() const { return mPosition; }
	void SetPosition(const vec3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale;  mRecomputeWorldTransform = true; }

	vec3 GetRotation() const { return glm::eulerAngles(mRotation); }
	void SetRotation(vec3 eAngles) { mRotation = quat(eAngles);  mRecomputeWorldTransform = true; }
	
	void ComputeWorldTransform();

	const mat4& GetWorldTransform( ) const { return mWorldTransform; }

	vec3 GetForward() const { return mRotation * -UNIT_Z_V3; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

protected:
	// Actor's state
	State mState;

	// Transform
	mat4 mWorldTransform;

	vec3 mPosition;
	float mScale;
	quat mRotation;
	bool mRecomputeWorldTransform;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};
