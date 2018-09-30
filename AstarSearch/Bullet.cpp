// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#include "Bullet.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Project1Game.h"
#include "Enemy.h"

Bullet::Bullet(class Project1Game* game, bool friendly)
	:Actor(game),
	FRIENDLY(friendly)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Projectile.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(400.0f);

	Cc = new CircleComponent(this);
	Cc->SetRadius(5.0f);

	mLiveTime = 1.0f;
}

void Bullet::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	if (FRIENDLY) {
		// Check for collision vs enemies
		std::vector<Enemy*> enemies = ((Project1Game*)GetGame())->GetEnemies();
		if (enemies.size() <= 0) return;
		for (Enemy* e : enemies)
		{
			if (Intersect(*Cc, *(e->GetCircle())))
			{
				// We both die on collision
				// TODO: Just damage enemy on hit and enemy will destroy itsef
				((Project1Game*)GetGame())->RemoveEnemy(e);
				e->SetState(EDead);
				SetState(EDead);
				break;
			}
		}
	}
	else {
		Walker* w = ((Project1Game*)GetGame())->getWalker();
		if (Intersect(*Cc, *(w->getCircle()))) {

		}
	}

	mLiveTime -= deltaTime;
	if (mLiveTime <= 0.0f)
	{
		// Time limit hit, die
		SetState(EDead);
	}
}

Bullet::~Bullet() {
	delete Cc;
}
