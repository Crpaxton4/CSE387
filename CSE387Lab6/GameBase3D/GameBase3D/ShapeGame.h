#pragma once
#include "Game.h"
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

};

