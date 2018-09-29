#pragma once
#include "Actor.h"
#include "SpriteSheetAnimCompnent.h"
#include "CircleComponent.h"
#include<map>
#include <string>

class Walker :
	public Actor
{
public:
	Walker(class Game* game);
	void ActorInput(const uint8_t* keyState) override;
	void UpdateActor(float deltaTime) override;

private:
	float laserCooldown;
	float missileCooldown;
	float speed = 150.0f;
	bool mDead = false;
	int hits;
	std::string curAnim;
	bool idling;

	vec2 moveVector;

	SpriteSheetAnimCompnent* SSc;
	CircleComponent* Cc;


};

