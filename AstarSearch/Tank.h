#pragma once
#include "Enemy.h"
#include "Project1Game.h"
#include "SpriteSheetAnimCompnent.h"

class Tank :
	public Enemy
{
public:
	Tank(Project1Game* g);
	void UpdateActor(float deltaTime);
	~Tank();

private:
	float bulletCoolDown;
	float moveTimer;
	SpriteSheetAnimCompnent* SSc;
	const float MAX_SPEED = 2.0f;
	int tankId;
	int x, y;
};

