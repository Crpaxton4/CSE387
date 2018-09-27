#pragma once
#include "Actor.h"
#include "MultiAnimSpriteComponent.h"
class MyMultiActor :
	public Actor
{
	public:
	MyMultiActor( Game* game );

	void ActorInput( const uint8_t* keyState ) override;

	MultiAnimSpriteComponent * masc;
};

