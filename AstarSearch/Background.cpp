#include "Background.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Project1Game.h"


Background::Background(Project1Game* game)
	:Actor(game)
{
	Sc = new SpriteComponent(this, 10);
	Sc->SetTexture(GetGame()->GetTexture("Assets/GrassBackground.png"));
	SetPosition(vec2(1024 / 2, 768 / 2));
}

Background::~Background()
{
}
