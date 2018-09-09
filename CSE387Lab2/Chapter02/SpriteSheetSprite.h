#pragma once
#include "Actor.h"
class SpriteSheetSprite :
	public Actor
{
public:
	SpriteSheetSprite(class Game* game);
	~SpriteSheetSprite();

	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetLateralSpeed() const { return lateralSpeed; }
	float GetVerticalSpeed() const { return verticalSpeed; }

private:
	float lateralSpeed;
	float verticalSpeed;
};

