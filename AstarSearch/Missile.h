#pragma once
#include "Actor.h"
#include "Enemy.h"
#include "PhysicalMovementComponent.h"
#include "SpriteSheetAnimCompnent.h"
#include "CircleComponent.h"

class Missile :
	public Actor
{
public:
	Missile(class Game* game, float rotation, bool friendly = false);
	void UpdateActor(float deltaTime) override;
	vec2 Seek(vec2 targetPos);

private:
	CircleComponent* Cc;
	SpriteSheetAnimCompnent* SSc;
	PhysicalMovementComponent* PMc;

	float deathTimer;
	float exploded = false;
	const bool FRIENDLY;
	const float MAX_SPEED = 300.0f;

};

