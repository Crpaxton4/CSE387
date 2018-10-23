// From Game Programming in C++ by Sanjay Madhav
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "CircleComponent.h"
class Bullet : public Actor
{
public:
	Bullet(class Project1Game* game, bool friendly = true);
	~Bullet();
	void UpdateActor(float deltaTime) override;
private:
	CircleComponent* Cc;
	float mLiveTime;
	const bool FRIENDLY;
};
