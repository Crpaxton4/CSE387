#pragma once
#include "Game.h"
class Project1Game :
	public Game
{
public:
	Project1Game();
	~Project1Game();

protected:
	void LoadData() override;
	void UnloadData() override;
};

