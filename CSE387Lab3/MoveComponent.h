// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "MathLibsConstsFuncs.h"
#include <vector>

class MoveComponent : public Component
{
public:
	// Lower update order to update first
	MoveComponent(class Actor* owner, float mass, int updateOrder = 10);

	void Update(float deltaTime) override;

	void AddForce(float magnitude);
	float GetAngularSpeed() const { return mAngularSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetMaxForwardSpeed(float max) { maxForwardSpeed = max; }
	float GetMaxForwardSpeed() { return maxForwardSpeed; }
	void SetMaxImpulse(float impulse) { maxImpulse = impulse; }
	float GetMaxImpulse() { return maxImpulse; }
	void Reset();

private:
	// Controls rotation (radians/second)
	float mAngularSpeed;
	float maxForwardSpeed;
	float maxImpulse;

	float mMass;

	vec2 totalForce;
	vec2 mAcceleration;
	vec2 mVelocity;
};
