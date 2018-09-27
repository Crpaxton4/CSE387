#pragma once
#include "Actor.h"



class EqualWeightEdgeGraph :
	public Actor
{
	public:
	EqualWeightEdgeGraph( class Game* game );

	// Search for shortest path
	void UpdateActor( float deltaTime ) override;

	protected:

	struct Graph * mGraph;

	bool searchComplete = false;

	struct GraphNode * mStart;
	struct GraphNode * mEnd;

};

