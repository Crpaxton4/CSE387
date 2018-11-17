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
,mAngularEulerSpeeds(vec3(0.0f, 0.0f , 0.0f ))
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{

		mOwner->SetRotation( mOwner->GetRotation( ) * 
							 glm::rotate(mAngularEulerSpeeds.y, glm::normalize(mAngularEulerSpeeds )));
	
	if (!NearZero(mForwardSpeed))
	{
		vec3 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		mOwner->SetPosition(pos);
	}
}
