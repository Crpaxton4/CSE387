#include "Spawner.h"
#include "Plane.h"
#include "Tank.h"
#include <iostream>


Spawner::Spawner(Project1Game* game)
	:Actor(game)
{
	SpriteComponent* Sc = new SpriteComponent(this);
	Sc->SetTexture(game->GetTexture("Assets/Carrier.png"));
	SetPosition(vec2(1024 - 95, 140));
	SetScale(0.6f);
}

void Spawner::UpdateActor(float deltaTime) {
	tankSpawnTimer -= deltaTime;
	planeSpawnTimer -= deltaTime;

	srand(deltaTime);
	float r1 = (float)rand() / (float)RAND_MAX;

	srand(deltaTime*deltaTime);
	float r2 = (float)rand() / (float)RAND_MAX;

	if (tankSpawnTimer < 0) {
		Tank* t = new Tank((Project1Game*)GetGame());
		t->SetPosition(GetPosition() + vec2(r1 * -250.0f, r2 * 250.0f));
		tankSpawnTimer = 10.0f;
	}

	if (planeSpawnTimer < 0) {
		Plane* p = new Plane((Project1Game*)GetGame());
		p->SetPosition(GetPosition() + vec2(r1 * -250.0f, r2 * 250.0f));
		planeSpawnTimer = 9.0f;
	}
}


Spawner::~Spawner()
{
}
