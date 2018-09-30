#include "Missile.h"
#include "Actor.h"
#include "Project1Game.h"
#include "MathLibsConstsFuncs.h"
#include <iostream>

Missile::Missile(Game* game, float rotation, bool friendly)
	: Actor(game),
	FRIENDLY(friendly),
	deathTimer(0.0f)
{
	SetRotation(rotation);
	std::cout << rotation << std::endl;

	SSc = new SpriteSheetAnimCompnent(this, true); //uses rotation when drawing the sprite

	SpriteSheetAnimation alive;
	alive.startingFrame = vec2(4, 4);
	alive.endingFrame = vec2(4, 4);
	alive.frameSize = vec2(64, 64);
	alive.rowColumns = vec2(5, 5);
	alive.textureName = "Assets/Explosion.png";
	alive.framePerSec = 24.0f;
	alive.loopTimes = -1;

	SpriteSheetAnimation explode;
	explode.startingFrame = vec2(0, 0);
	explode.endingFrame = vec2(3, 4);
	explode.frameSize = vec2(64, 64);
	explode.rowColumns = vec2(5, 5);
	explode.textureName = "Assets/Explosion.png";
	explode.framePerSec = 24.0f;
	explode.loopTimes = -1;

	SSc->AddAnimation("alive", alive, false);
	SSc->AddAnimation("explode", explode, false);

	Cc = new CircleComponent(this);
	Cc->SetRadius(56.0f);

	PMc = new PhysicalMovementComponent(this, 25.0f, 0.1f, MAX_SPEED/3.0f);

	SSc->PlayAnimation("alive");
}

void Missile::UpdateActor(float deltaTime) {
	deathTimer += deltaTime;

	if (exploded && deathTimer > 6.0f) {
		SetState(EDead);

	}else if (deathTimer > 5.0f && !exploded) {
		
		SSc->PlayAnimation("explode");
		delete PMc;
		delete Cc;
		exploded = true;
	}

	if (exploded) return; //dont do anything if exploding/exploded

	if (FRIENDLY) {
		PMc->addForce(GetForward()*MAX_SPEED/2.0f);
		PMc->addForce(Seek(((Project1Game*)GetGame())->GetNearestEnemy(GetPosition())->GetPosition()));
	}
	else {

		Project1Game* g = (Project1Game*)GetGame();
		Actor* w = g->getWalker();
		vec2 wPos = w->GetPosition();
		
		PMc->addForce(Seek(wPos));
	}
	

}

vec2 Missile::Seek(vec2 targetPos) {
	vec2 desiredVelocity = targetPos - GetPosition();
	desiredVelocity = MAX_SPEED * glm::normalize(desiredVelocity);

	vec2 steerForce = desiredVelocity - PMc->getVelocity();

	steerForce = glm::normalize(steerForce) * 300.0f;

	return steerForce;
}