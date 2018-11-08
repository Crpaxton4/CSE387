#pragma once
#include "Actor.h"

class ShapeGameActor :	public Actor
{
	public:
	ShapeGameActor( class ShapeGame* game );

	class ShapeGame* GetShapeGame( );
};

