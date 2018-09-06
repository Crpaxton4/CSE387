// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpaceGame.h"

int main(int argc, char** argv)
{
	SpaceGame sgame("CSE 387 paxtoncr Lab 2");
	bool success = sgame.Initialize();
	if (success)
	{
		sgame.RunLoop();
	}
	sgame.Shutdown();
	return 0;
}
