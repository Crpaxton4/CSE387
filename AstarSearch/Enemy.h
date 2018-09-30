// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "CircleComponent.h"

class Enemy : public Actor
{
public:
	Enemy(class Project1Game* game);
	~Enemy();
	virtual void UpdateActor(float deltaTime) override;
	class CircleComponent* GetCircle() { return Cc; }
	
protected:
	CircleComponent* Cc;
};
