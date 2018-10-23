#pragma once
#include "Game.h"
#include "Walker.h"
class Project1Game :
	public Game
{
public:
	Project1Game();

	class Actor* GetNearestEnemy(const vec2& pos);
	std::vector<class Enemy*>& GetEnemies() { return enemies; }
	Walker* getWalker() { return walker; }
	void addEnemy(Enemy* e) { enemies.push_back(e); }
	void RemoveEnemy(Enemy* e);

protected:
	void LoadData() override;
	void ProcessInput() override;

private:
	void SetWalker(Walker* w) { walker = w; }
	std::vector<class Enemy*> enemies;
	Walker* walker;


};

