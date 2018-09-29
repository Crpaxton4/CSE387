#include "Walker.h"
#include "SpriteSheetAnimCompnent.h"
#include "Project1Game.h"
#include <iostream>



Walker::Walker(Game* game)
	:Actor(game),
	laserCooldown(0.0f),
	missileCooldown(0.0f),
	hits(0)
{
	SSc = new SpriteSheetAnimCompnent(this, 150);

	std::vector<std::string> animationNames = {
		"down",
		"down-right",
		"right",
		"up-right",
		"up",
		"up-left",
		"left",
		"down-left"
	};

	// Create active animations
	SpriteSheetAnimation anim;
	for (int i = 0; i < animationNames.size(); i++) {
		//each animation is one row long
		anim.startingFrame = vec2(0, i);
		anim.endingFrame = vec2(15, i);
		anim.frameSize = vec2(64, 64);
		anim.rowColumns = vec2(16, 8);
		anim.textureName = "Assets/walker.png";
		anim.framePerSec = 24.0f;
		anim.loopTimes = -1;
		
		SSc->AddAnimation(animationNames[i], anim, false);
	}

	//Create idle animations
	for (int i = 0; i < animationNames.size(); i++) {
		//just neutral frames found in the sprite sheet
		// they happen to be in predictable places which is nice
		int idleFrame;
		if (i < 4) idleFrame = 10;
		else idleFrame = 2;

		anim.startingFrame = vec2(idleFrame, i);
		anim.endingFrame = vec2(idleFrame, i);
		anim.frameSize = vec2(64, 64);
		anim.rowColumns = vec2(8, 16);
		anim.textureName = "Assets/walker.png";
		anim.framePerSec = 24.0f;
		anim.loopTimes = -1;

		SSc->AddAnimation(animationNames[i] + "-idle", anim, false);
	}

	// Create CircleComponent for colisions
	Cc = new CircleComponent(this);
	Cc->SetRadius(64.0f);

	curAnim = "right-idle";
	idling = true;
	SSc->PlayAnimation(curAnim);


}

void Walker::UpdateActor(float deltaTime) {
	vec2 pos = GetPosition();
	pos.x += speed * moveVector.x * deltaTime;
	pos.y += speed * moveVector.y * deltaTime;

	//TODO: add resizing. get dimensions from game;

	float gHeight = 768.0f;
	float gWidth = 1024.0f;

	float padding = 32.0f;

	if (pos.x < padding)
	{
		pos.x = padding;
	}
	else if (pos.x > gWidth - padding)
	{
		pos.x = gWidth - padding;
	}
	if (pos.y < padding)
	{
		pos.y = padding;
	}
	else if (pos.y > gHeight - padding)
	{
		pos.y = gHeight-padding;
	}
	SetPosition(pos);
}

void Walker::ActorInput(const uint8_t* keyState) {

	bool up, down, left, right, shootMissile, shootLaser, idle;

	up = keyState[SDL_SCANCODE_W];
	down = keyState[SDL_SCANCODE_S];
	right = keyState[SDL_SCANCODE_D];
	left = keyState[SDL_SCANCODE_A];
	shootLaser = keyState[SDL_SCANCODE_SPACE];
	shootMissile = keyState[SDL_SCANCODE_M];

	moveVector = vec2(0, 0);
	std::string prevAnim = curAnim;

	

	// not idle if any key is pressed
	idle = !(up || down || left || right);

	if (idle) {
		if(!idling) curAnim += "-idle";
		moveVector = vec2(0.0f, 0.0f);
		idling = true;

	}else if (down) {
		idling = false;
		if (right) {
			curAnim = "down-right";
			moveVector = vec2(0.5f, 0.5f);
		}
		else if (left) {
			curAnim = "down-left";
			moveVector = vec2(-0.5f, 0.5f);
		}
		else {
			curAnim = "down";
			moveVector = vec2(0.0f, 0.75f);
		}
	}
	else if (up) {
		idling = false;
		if (right) {
			curAnim = "up-right";
			moveVector = vec2(0.5f, -0.5f);
		}
		else if (left) {
			curAnim = "up-left";
			moveVector = vec2(-0.5f, -0.5f);
		}
		else {
			curAnim = "up";
			moveVector = vec2(0.0f, -0.75f);
		}
	}
	else if (right) {
		idling = false;
		curAnim = "right";
		moveVector = vec2(1.0f, 0.0f);
	}
	else if (left) {
		idling = false;
		curAnim = "left";
		moveVector = vec2(-1.0f, 0.0f);
	}

	std::cout << curAnim << std::endl;
	if (prevAnim != curAnim) {
		SSc->PlayAnimation(curAnim);
	}

	if (shootLaser && laserCooldown <= 0.0f) {
		// Spawn laser 
	}

	if (shootMissile && missileCooldown <= 0) {
		// Spawn Missile
	}
}
