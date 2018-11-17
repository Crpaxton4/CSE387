// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "PlaneStates.h"
#include "AIComponent.h"
#include "Project1Game.h"
#include "Walker.h"
#include "Missile.h"
#include "Actor.h"
#include <iostream>
#include <SDL/SDL_log.h>
#include <Windows.h>

void PlanePatrol::Update(float deltaTime)
{
	SDL_Log("Updating %s state | orbitCenter: (%f, %f)", GetName(), orbitCenter.x, orbitCenter.y);

	//circle the selected point at a radius
	Walker* nearby = gameOwner->getWalker();

	float dist = glm::distance(nearby->GetPosition(), planeOwner->GetPosition());

	if (dist < attackRange) {
		mOwner->ChangeState("Attack");
	}
	else {
		float x; //burner variable because modf is picky
		float rotation = planeOwner->GetRotation() - 1.065f*PI * modf(deltaTime, &x); //scale it so one roation per second
		planeOwner->SetRotation(rotation);
		planeOwner->SetPosition(orbitCenter - vec2(glm::cos(rotation), -glm::sin(rotation)) * orbitRadius); //Specific case of 2d normal vector v = (x, y), normal(v) = (y, -x)
		std::cout << rotation << std::endl;
		std::cout << planeOwner->GetPosition().x << " | " << planeOwner->GetPosition().y << std::endl;

	}

}

void PlanePatrol::OnEnter()
{
	SDL_Log("Entering %s state", GetName());

	// pick a point to circle
	orbitCenter = planeOwner->GetPosition() + vec2(orbitRadius, orbitRadius); // make sure that the plane will be inside the window 

	std::cout << planeOwner->GetPosition().x << " | " << planeOwner->GetPosition().y << std::endl;

	planeOwner->changeAnimation("circle");

}

void PlanePatrol::OnExit()
{
	SDL_Log("Exiting %s state", GetName());

	// Nothing afaict
}

void PlaneDeath::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());

	// nothing. clean up onenter
}

void PlaneDeath::OnEnter()
{
	SDL_Log("Entering %s state", GetName());

	// mark this actor as dead
	//gameOwner->RemoveEnemy(planeOwner);
	planeOwner->SetState(Actor::EDead);
}

void PlaneDeath::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
	// terminal state. No exiting
}

void PlaneAttack::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());

	//Seek the walker

	Walker* w = gameOwner->getWalker();
	float dist = glm::distance(w->GetPosition(), planeOwner->GetPosition());
	if (dist > attackRange) {
		mOwner->ChangeState("Patrol");
	}
	float rotation = planeOwner->GetRotation();
	vec2 atDir = w->GetPosition() - planeOwner->GetPosition();

	planeOwner->SetRotation(atan2(-atDir.y, atDir.x) + PI/2.0f); // constant sprite is rotated 90 degrees so rotate it back

	vec2 pos = planeOwner->GetPosition() + glm::normalize(w->GetPosition() - planeOwner->GetPosition()) * 1.0f;

	planeOwner->SetPosition(pos);

	missileTimer -= deltaTime;

	if (missileTimer <= 0) {
		missileTimer = 8.0f;
		//launch missile
		Missile* m = new Missile(planeOwner->GetGame(), planeOwner->GetRotation(), false);
		m->SetPosition(planeOwner->GetPosition());
	}

}

void PlaneAttack::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
	//change animation and SSc rotation usage
	planeOwner->changeAnimation("constant");
}

void PlaneAttack::OnExit()
{
	SDL_Log("Exiting %s state", GetName());

}
