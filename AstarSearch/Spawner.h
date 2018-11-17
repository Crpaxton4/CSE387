#pragma once
#include "Actor.h"
#include "Project1Game.h"
class Spawner :
	public Actor
{
public:
	Spawner(Project1Game* game);
	void UpdateActor(float deltaTime) override;
	~Spawner();

private:
	float planeSpawnTimer;
	float tankSpawnTimer;
};

