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
#include <iostream>

Ship::Ship(Game* game)
	:Actor(game)
	, mLaserCooldown(0.0f)
{
	// Create a sprite component
	mSprite = new SpriteComponent(this, 150);
	mSprite->SetTexture(game->GetTexture("Assets/Ship.png"));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);

	// Create an input component and set keys/speed
	ic = new InputComponent(this, 5.0f);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxImpulse(2000.0f);
	ic->SetMaxAngularSpeed(TWO_PI);
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	if (mDead) {
		mDeadTimer += deltaTime;

		if (mDeadTimer >= 2.0f) { // death delay is over
			GetGame()->AddSprite(mSprite);
			AddComponent(mSprite); // Prevents exception when game is exeted while ship is 'dead'
			ic->Reset();
			mDeadTimer = 0.0f;


			// Reset ship position and orientation
			SetPosition(vec2(512.0f, 384.0f));
			SetRotation(PI_OVER_2);


			mDead = false; //now alive
		}
	}
	else { // if alive check for intersections
		for (auto ast : GetGame()->GetAsteroids()) {
			if (Intersect(*mCircle, *(ast->GetCircle()))) {
				mDead = true;

				// remove the sprite from the game
				GetGame()->RemoveSprite(mSprite);
				RemoveComponent(mSprite);  // Prevents exception when game is exeted while ship is 'dead'
				RemoveComponent(mSprite);  // Prevents exception when game is exeted while ship is 'dead'
				break;
			}
		}
	}


}

void Ship::ActorInput(const uint8_t* keyState)
{

	if (mDead) return; // save a little computation and dont do specific input if dead

	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		laser->Launch();
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
