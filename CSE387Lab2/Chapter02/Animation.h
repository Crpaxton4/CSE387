#pragma once

struct Animation {
	int startIndex;
	int numFrames;
	SDL_Texture* spriteSheetTexture;

	Animation(){}; // 
	Animation(int s, int f, SDL_Texture* t) {
		startIndex = s;
		numFrames = f;
		spriteSheetTexture = t;
	}
};

