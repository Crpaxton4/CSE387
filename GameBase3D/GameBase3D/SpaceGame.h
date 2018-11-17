#pragma once
#include "Game.h"
class SpaceGame :
	public Game
{
	public:
	SpaceGame( );

	void LoadData( ) override;

	// Game-specific (add/remove asteroid)
	void AddAsteroid( class Asteroid* ast );
	void RemoveAsteroid( class Asteroid* ast );
	std::vector<class Asteroid*>& GetAsteroids( ) { return mAsteroids; }

	protected:

	// Game-specific
	class Ship* mShip;
	std::vector<class Asteroid*> mAsteroids;
};

