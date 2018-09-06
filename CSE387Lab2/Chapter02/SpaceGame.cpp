#include "SpaceGame.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

SpaceGame::SpaceGame(std::string windowTitle) {
	this->windowTitle = windowTitle;
}

//bool SpaceGame::Initialize() {
//	bool b = Game::Initialize();
//	LoadData();
//	return b;

//}

void SpaceGame::ProcessInput() {
	SDL_Event event;
	// Keep processing events until the queue is empty
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

			// If we get an SDL_QUIT event, end the game loop
		case SDL_QUIT:
			std::cout << "Window closed. Quitting." << std::endl;
			mIsRunning = false;
			break;
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape was pressed, end the game loop
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	//Override this in Space Game: Call super then call this in SpaceGame::processInput
	// Process ship input
	mShip->ProcessKeyboard(state);
}

void SpaceGame::LoadData()
{
	// Create player's ship
	mShip = new Ship(this);
	mShip->SetPosition(vec2(100.0f, 384.0f));
	mShip->SetScale(1.5f);

	// Create actor for the background (this doesn't need a subclass)
	Actor* temp = new Actor(this);

	// Set position to the center of the window
	temp->SetPosition(vec2(mWindowWidth / 2, mWindowHeight / 2));

	// Create the "far back" background component to for the temp Actor
	BGSpriteComponent* bg = new BGSpriteComponent(temp);

	// Set the size of the background component to match the window dimensions
	bg->SetScreenSize(vec2(mWindowWidth, mWindowHeight));

	// Create a vector of textures and get them loaded
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};

	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);

	// Create the closer background
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(vec2(mWindowWidth, mWindowHeight));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}

void SpaceGame::UnloadData()  {

}