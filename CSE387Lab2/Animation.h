#pragma once

struct Animation {
	int startIndex;
	int numFrames;

	Animation(){};
	Animation(int s, int f) {
		startIndex = s;
		numFrames = f;
	}
};

