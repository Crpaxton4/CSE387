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

class MoveComponent : public Component
{
public:
	// Lower update order to update first
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;
	
	vec3 GetAngularSpeed() const { return mAngularEulerSpeeds; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(vec3 eulerSpeeds) { mAngularEulerSpeeds = eulerSpeeds; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
	vec3 mAngularEulerSpeeds;
	float mForwardSpeed;
};
