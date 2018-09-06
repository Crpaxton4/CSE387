#pragma once
#include "SDL/SDL.h"
#include "Game.h"
#include "Ship.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>


class SpaceGame : public Game
{
public:
	// Abstract out parts of Game class that are specific tothis game
	SpaceGame(std::string windowTitle);
	void LoadData();
	bool Initialize();

private:
	// Game-specific
	Ship* mShip; // Player's ship
};

