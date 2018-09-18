#pragma once
#include "SDL/SDL.h"
#include "Game.h"
#include "SpriteSheetActor.h"
#include "BGSpriteComponent.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>


class SpaceGame : public Game
{
public:
	// Abstract out parts of Game class that are specific tothis game
	SpaceGame(std::string windowTitle);
	void LoadData() override;
	void UnloadData() override;
	void ProcessInput() override;

private:
	// Game-specific
	SpriteSheetActor* player; // Player	
	Actor* BGActor;
	BGSpriteComponent* bg;
	BGSpriteComponent* stars;

	float bgSpeed = -100.0f;
	
	
	


};

