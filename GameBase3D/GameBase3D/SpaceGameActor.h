#pragma once
#include "Actor.h"

class SpaceGameActor :	public Actor
{
	public:
	SpaceGameActor( class SpaceGame* game );

	class SpaceGame* GetSpaceGame( );
};

