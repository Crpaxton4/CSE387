#pragma once
#include "AnimSpriteComponent.h"
#include "Animation.h"

class MultiAnimSpriteComponent : public AnimSpriteComponent
{
public:
	MultiAnimSpriteComponent();
	~MultiAnimSpriteComponent();

	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltaTime) override;

private:
	int frameHeight;
	int frameWidth;

	// Collection of individual animations in the sprite sheet
	std::vector<Animation> animations;
};

