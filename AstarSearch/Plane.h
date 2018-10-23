#pragma once
#include "Enemy.h"
#include "MoveComponent.h"
#include "AIComponent.h"
#include "SpriteSheetAnimCompnent.h"
#include "PhysicalMovementComponent.h"

class Plane :
	public Enemy
{
public:
	Plane(class Project1Game* game);
	void changeAnimation(std::string animation);
	~Plane();
	void Damage(bool missile = false) override;
private:
	float missileCooldown;
	float hitTimer;

	
	SpriteSheetAnimCompnent* SSc;
	MoveComponent* Mc;
	PhysicalMovementComponent* PMc;
	AIComponent* AIc;
};

