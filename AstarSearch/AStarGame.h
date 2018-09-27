#pragma once
#include "Game.h"
class AStarGame :
	public Game
{
	public:
	AStarGame( );
	~AStarGame( );

	class Grid* GetGrid( ) { return mGrid; }
	std::vector<class Enemy*>& GetEnemies( ) { return mEnemies; }
	class Enemy* GetNearestEnemy( const vec2& pos );

	protected:

	virtual void ProcessInput( ) override;
	virtual void LoadData( ) override;

	// Game-specific
	std::vector<class Enemy*> mEnemies;
	class Grid* mGrid;
	float mNextEnemy;

};

