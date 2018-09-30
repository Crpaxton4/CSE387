#include "Project1Game.h"
#include "Walker.h"
#include "Enemy.h"
#include "Plane.h"
#include "Background.h"
#include "Spawner.h"


Project1Game::Project1Game() :Game()
{
}

void Project1Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;

}

void Project1Game::LoadData() {
	// Create new Walker on the bottom left corner of the screen
	Walker* walker = new Walker(this);
	walker->SetPosition(vec2(100.0f, 100.0f));
	walker->SetScale(0.75f);

	SetWalker(walker);
	//Create enemy Base in the top right corner (no need to add enemies because base handles that)
	Spawner* spawn = new Spawner(this);
	//possibly create background, but may just use solid colors
	Background* bg = new Background(this);
}

Actor* Project1Game::GetNearestEnemy(const vec2& pos) {
	Enemy* closest = nullptr;
	for (Enemy* e : enemies) {
		if (closest == nullptr) {
			closest = e;
		}
		else if (glm::length(closest->GetPosition() - pos) > glm::length(e->GetPosition() - pos)) {
			closest = e;
		}
	}

	return closest;
}

void Project1Game::RemoveEnemy(Enemy* e) {
	auto iter = std::find(enemies.begin(), enemies.end(), e);
	if (iter != enemies.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, enemies.end() - 1);

		Enemy* e = enemies[enemies.size() - 1];
		e->SetState(Actor::EDead);
		enemies.pop_back();
	}
}

