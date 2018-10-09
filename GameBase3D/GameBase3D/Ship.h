// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SpaceGameActor.h"
class Ship : public SpaceGameActor
{
public:
	Ship(class SpaceGame* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
private:
	float mLaserCooldown;
};