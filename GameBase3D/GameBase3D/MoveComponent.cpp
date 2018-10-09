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

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
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
	
	if (!NearZero(mForwardSpeed))
	{
		vec2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		int width = mOwner->GetGame( )->getWindowWidth( );
		int height = mOwner->GetGame( )->getWindowHeight( );

		// Screen wrapping
		if (pos.x < -width/2.0f) { pos.x = width / 2.0f; }
		else if (pos.x > width / 2.0f ) { pos.x = -width / 2.0f; }
		if (pos.y < -height/2.0f) { pos.y = height / 2.0f; }
		else if (pos.y > height / 2.0f ) { pos.y = -height / 2.0f; }
		mOwner->SetPosition(pos);
	}
}
