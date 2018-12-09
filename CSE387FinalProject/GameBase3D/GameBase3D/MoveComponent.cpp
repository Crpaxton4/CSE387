// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mForwardSpeed(0.0f)
,rotateXYSpeeds(vec2(0.0, 0.0))
{
	
}

void MoveComponent::Update(float deltaTime)
{

	vec3 xBase = glm::normalize(glm::cross(mOwner->GetForward(), vec3(0.0, 1.0, 0.0)));
	vec3 yBase = glm::normalize(glm::cross(xBase, mOwner->GetForward()));

	mat4 xRotation = glm::rotate(glm::radians(rotateXYSpeeds.x), xBase);
	mat4 yRotation = glm::rotate(glm::radians(rotateXYSpeeds.y), yBase);

	mat4 rotation = mOwner->GetRotation() * yRotation * xRotation;

		mOwner->SetRotation( rotation );

	if (!NearZero(mForwardSpeed))
	{
		vec3 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		mOwner->SetPosition(pos);
	}
}
