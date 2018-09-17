// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "Asteroid.h"
#include <windows.h>

Ship::Ship(Game* game)
	:Actor(game)
	, mLaserCooldown(0.0f)
{
	// Create a sprite component
	mSprite = new SpriteComponent(this, 150);
	mSprite->SetTexture(game->GetTexture("Assets/Ship.png"));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(TWO_PI);
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	if (mDead) {
		mDeadTimer += deltaTime;

		if (mDeadTimer >= 2.0f) { // death delay is over
			GetGame()->AddSprite(mSprite);
			mDeadTimer = 0.0f;
			mDead = false; //now alive
		}
	}
	else { // if alive check for intersections
		for (auto ast : GetGame()->GetAsteroids()) {
			if (Intersect(*mCircle, *(ast->GetCircle()))) {
				mDead = true;
				// Reset ship position and orientation
				SetPosition(vec2(512.0f, 384.0f));
				SetRotation(PI_OVER_2);

				// remove the sprite from the game
				GetGame()->RemoveSprite(mSprite);
				break;
			}
		}
	}


}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
	}

	if (keyState[SDL_SCANCODE_W]) {
		mSprite->SetTexture(GetGame()->GetTexture("Assets/ShipWithThrust.png"));
	}
	else {
		mSprite->SetTexture(GetGame()->GetTexture("Assets/Ship.png"));
	}
}
