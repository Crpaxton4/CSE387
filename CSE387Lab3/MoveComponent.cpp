// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "Actor.h"
#include <iostream>

MoveComponent::MoveComponent(class Actor* owner, float mass, int updateOrder)
	:Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mMass(mass)
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}

	mAcceleration = totalForce/mMass;

	
	mVelocity += mAcceleration * deltaTime;

	float currForwardSpeedSquared = (mVelocity.x * mVelocity.x) + (mVelocity.y * mVelocity.y);

	if (currForwardSpeedSquared > (maxForwardSpeed*maxForwardSpeed)) { //Clamp the velocity to a magnitude =maxForwardSpeed
		mVelocity *= sqrt(maxForwardSpeed*maxForwardSpeed/currForwardSpeedSquared);
	}

	vec2 pos = mOwner->GetPosition();
	pos += mVelocity * deltaTime;

	// (Screen wrapping code only for asteroids)
	if (pos.x < 0.0f) { pos.x = 1022.0f; }
	else if (pos.x > 1024.0f) { pos.x = 2.0f; }

	if (pos.y < 0.0f) { pos.y = 766.0f; }
	else if (pos.y > 768.0f) { pos.y = 2.0f; }

	mOwner->SetPosition(pos);


	totalForce = vec2(0, 0);
}

void MoveComponent::AddForce(float magnitude) { // Only applies forward force for now
	if(magnitude > maxImpulse) magnitude = maxImpulse;
	vec2 force = mOwner->GetForward()*magnitude;
	totalForce += force;
}

void MoveComponent::Reset() {
	mAcceleration = vec2(0.0f, 0.0f);
	mVelocity = vec2(0.0f, 0.0f);
	mAngularSpeed = 0.0f;
	totalForce = vec2(0.0f, 0.0f);
}