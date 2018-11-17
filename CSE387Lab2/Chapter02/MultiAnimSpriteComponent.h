#pragma once
#include "AnimSpriteComponent.h"
#include "Animation.h"

class MultiAnimSpriteComponent : public SpriteComponent
{
public:
	MultiAnimSpriteComponent();
	~MultiAnimSpriteComponent();

	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltaTime) override;
	void SetTexture(SDL_Texture* texure) override;


private:
	int frameHeight;
	int frameWidth;

	// Collection of individual animations in the sprite sheet
	std::vector<Animation> animations;

	
};

