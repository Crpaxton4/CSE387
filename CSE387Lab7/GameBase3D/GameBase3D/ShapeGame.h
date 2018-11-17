#pragma once
#include "Game.h"
#include "ShapeGameActor.h"
class ShapeGame :
	public Game
{
	public:
		ShapeGame( );

		void LoadData( ) override;

		void SetupLighting();

		// Game-specific 

	protected:

		// Game-specific
		ShapeGameActor* mSunActor;
		ShapeGameActor* mEarthActor;
		ShapeGameActor* mMoonActor;

};

