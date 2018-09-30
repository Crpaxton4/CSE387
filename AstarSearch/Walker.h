#pragma once
#include "Actor.h"
#include "SpriteSheetAnimCompnent.h"
#include "CircleComponent.h"
#include "PhysicalMovementComponent.h"
#include<map>
#include <string>

class Walker :
	public Actor
{
public:
	Walker(class Project1Game* game);
	void ActorInput(const uint8_t* keyState) override;
	void UpdateActor(float deltaTime) override;
	CircleComponent* getCircle() { return Cc; }

private:
	float laserCooldown;
	float missileCooldown;
	float speed = 150.0f;
	bool mDead = false;
	int hits;
	std::string curAnim;
	bool idling;
	float hitTimer;

	vec2 moveVector;

	SpriteSheetAnimCompnent* SSc;
	CircleComponent* Cc;
	PhysicalMovementComponent* PMc;


};

