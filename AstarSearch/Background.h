#pragma once
#include "Actor.h"
class Background :
	public Actor
{
public:
	Background(class Project1Game* game);
	~Background();

private:
	class SpriteComponent* Sc;
};

