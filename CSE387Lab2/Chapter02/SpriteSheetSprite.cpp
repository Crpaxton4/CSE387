#include "SpriteSheetSprite.h"
#include "AnimSpriteComponent.h"
#include "Game.h"


SpriteSheetSprite::SpriteSheetSprite(class Game* game)
	:Actor(game)
	, lateralSpeed(0.0f)
	, verticalSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png") //TODO: Put sprite sheet here
	};
	asc->SetAnimTextures(anims);
}


SpriteSheetSprite::~SpriteSheetSprite()
{
}

void SpriteSheetSprite::UpdateActor(float deltaTime) {
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	vec2 pos = GetPosition();
	pos.x += lateralSpeed * deltaTime;
	pos.y += verticalSpeed * deltaTime;
	// Restrict position to left half of screen
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	SetPosition(pos);
}

void SpriteSheetSprite::ProcessKeyboard(const uint8_t* state) {
	lateralSpeed = 0.0f;
	verticalSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		lateralSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		lateralSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		verticalSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		verticalSpeed -= 300.0f;
	}
}
