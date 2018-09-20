// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include "InputComponent.h"
#include <algorithm>

Enemy::Enemy(class Game* game)
:Actor(game)
{
	// Add to enemy vector
	game->GetEnemies().emplace_back(this);
	
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Airplane.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(200);

	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_D);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_A);
	ic->SetMaxAngularSpeed(300.0f);
	ic->SetAngularSpeed(PI_OVER_2);

	//// Set position at start tile
	//SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
	//// Setup a nav component at the start tile
	//NavComponent* nc = new NavComponent(this);
	//nc->SetForwardSpeed(150.0f);
	//nc->StartPath(GetGame()->GetGrid()->GetStartTile());
	// Setup a circle for collision
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
	// Remove from enemy vector
	auto iter = std::find(GetGame()->GetEnemies().begin(),
						  GetGame()->GetEnemies().end(),
						  this);
	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
	// Am I near the end tile?
	/*vec2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (NearZero(glm::length(diff), 10.0f))
	{
		SetState(EDead);
	}*/
}
