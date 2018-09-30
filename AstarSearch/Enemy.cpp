// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Enemy.h"
#include "Project1Game.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include <algorithm>

Enemy::Enemy(class Project1Game* game)
	:Actor(game),
	totalHealth(4)
{
	// Add to enemy vector
	game->GetEnemies().emplace_back(this);
}

Enemy::~Enemy()
{
	// Remove from enemy vector
	auto iter = std::find(((Project1Game*)GetGame())->GetEnemies().begin(),
		((Project1Game*)GetGame())->GetEnemies().end(),
		this);
	((Project1Game*)GetGame())->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}

void Enemy::Damage(bool missile) {
	if (missile) totalHealth -= 2;
	else totalHealth -= 1;

	if (totalHealth <= 0) {
		//remove self from game
		//((Project1Game*)GetGame())->RemoveEnemy(this);
		SetState(EDead);
	}
}
