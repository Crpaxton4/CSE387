#include "Walker.h"
#include "SpriteSheetAnimCompnent.h"
#include "Project1Game.h"
#include "Missile.h"
#include "Bullet.h"
#include <iostream>



Walker::Walker(Project1Game* game)
	:Actor(game),
	laserCooldown(0.0f),
	missileCooldown(0.0f),
	totalHealth(8),
	hitTimer(0.0f)
{
	SSc = new SpriteSheetAnimCompnent(this, false, 150);

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
	int idleFrame;
	for (int i = 0; i < animationNames.size(); i++) {
		// neutral frames found in the sprite sheet
		// they happen to be in predictable places which is nice
		
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

	// Set up PhysicalMovementComponent for projectile impulses
	PMc = new PhysicalMovementComponent(this, 1000.0f, 0.9f);
}

void Walker::UpdateActor(float deltaTime) {

	//update timers
	hitTimer -= deltaTime;
	missileCooldown -= deltaTime;
	laserCooldown -= deltaTime;

	//update position
	vec2 pos = GetPosition();
	pos.x += speed * moveVector.x * deltaTime;
	pos.y += speed * moveVector.y * deltaTime;

	//-----------------IMPORTANT-------------------
	//---------------------------------------------
	//TODO: add resizing. get dimensions from game;
	//---------------------------------------------
	//-----------------IMPORTANT-------------------

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
	if (pos.y < 192.0f)
	{
		pos.y = 192.0f; //Water line on background
	}
	else if (pos.y > gHeight - padding)
	{
		pos.y = gHeight-padding;
	}
	SetPosition(pos);
	SetRotation(atan2(-moveVector.y, moveVector.x)); // update roation for explosion impact

}

void Walker::ActorInput(const uint8_t* keyState) {
	//check hit timer. Dont allow input
	if (hitTimer > 0.0f) return;

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

	if (shootLaser && laserCooldown <= 0.0f) {
		// Spawn laser 
		Bullet* b = new Bullet((Project1Game*)GetGame());
		b->SetPosition(GetPosition());
		b->SetRotation(GetRotation());

		laserCooldown = 0.25f;
	}

	if (shootMissile && missileCooldown <= 0) {
		// Spawn Missile
		Missile* m = new Missile(GetGame(), GetRotation(), true);
		m->SetPosition(GetPosition());

		missileCooldown = 8.0f;
	}

	//----------------------------------
	// TEST STATEMENTS. DELETE WHEN DONE
	//----------------------------------

	// This works and looks right. 
	// Change getForward() to the vector between the two circle components (this-projectile)
	if (keyState[SDL_SCANCODE_H]) {
		PMc->addForce(this->GetForward() * -5000000.0f);
		hitTimer = 0.5f;
		if (!idling) curAnim += "-idle";
		moveVector = vec2(0.0f, 0.0f);
		idling = true;
	}

	//------------------------------------
	if (prevAnim != curAnim) {
		SSc->PlayAnimation(curAnim);
	}

}

void Walker::Damage( vec2 projectilePos, bool missile) {
	if (missile) totalHealth -= 2;
	else totalHealth -= 1;

	std::cout << "Walker Health: " << totalHealth << std::endl;

	//hit effect
	PMc->addForce(projectilePos - this->GetPosition() * 5000.0f);
	hitTimer = 0.5f;
	if (!idling) curAnim += "-idle";
	moveVector = vec2(0.0f, 0.0f);
	idling = true;

	if (totalHealth <= 0) {
		// Game Over
		GetGame()->End();
	}
}
