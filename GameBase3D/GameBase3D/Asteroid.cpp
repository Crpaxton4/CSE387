// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "SpaceGame.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(SpaceGame* game)
	:SpaceGameActor(game)
	,mCircle(nullptr)
{
	// Initialize to random position/orientation
	vec2 randPos = Random::GetVector(vec2(-game->getWindowWidth()/2.0f, -game->getWindowHeight( ) /2.0f ),
		vec2( game->getWindowWidth( )/2.0f, game->getWindowHeight( )/2.0f ));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, TWO_PI));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetSpaceGame()->RemoveAsteroid(this);
}