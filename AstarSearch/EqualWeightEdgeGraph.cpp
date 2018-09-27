#include "EqualWeightEdgeGraph.h"
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>


struct GraphNode
{
	std::string nodeName;
	// Adjacency list
	std::vector<GraphNode*> mAdjacent;

	GraphNode( std::string name = "noName" ) : nodeName( name ) { };
};

struct Graph
{
	// A graph contains nodes
	std::vector<GraphNode*> mNodes;
};

using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;


bool BFS( const Graph& graph, const GraphNode* start, const GraphNode* goal, NodeToParentMap& outMap )
{
	// Whether we found a path
	bool pathFound = false;
	// Nodes to consider
	std::queue<const GraphNode*> q;
	// Enqueue the first node
	q.emplace( start );

	while( !q.empty( ) ) {
		// Dequeue a node
		const GraphNode* current = q.front( );
		q.pop( );
		if( current == goal ) {
			pathFound = true;
			break;
		}

		// Enqueue adjacent nodes that aren't already in the queue
		for( const GraphNode* node : current->mAdjacent ) {
			// If the parent is null, it hasn't been enqueued
			// (except for the start node)
			const GraphNode* parent = outMap[node];
			if( parent == nullptr && node != start ) {
				// Enqueue this node, setting its parent
				outMap[node] = current;
				q.emplace( node );
			}
		}
	}

	return pathFound;
}

EqualWeightEdgeGraph::EqualWeightEdgeGraph( class Game* game )
	:Actor( game )
{
	// Build Figure 4.4 unweighted graph
	mGraph = new Graph( );

	GraphNode * zero = new GraphNode( "zero" );
	GraphNode * one = new GraphNode( "one" );
	GraphNode * two = new GraphNode( "two" );
	GraphNode * three = new GraphNode( "three" );

	zero->mAdjacent.emplace_back( two );

	one->mAdjacent.emplace_back( two );
	one->mAdjacent.emplace_back( three );

	two->mAdjacent.emplace_back( zero );
	two->mAdjacent.emplace_back( one );
	two->mAdjacent.emplace_back( three );

	three->mAdjacent.emplace_back( one );
	three->mAdjacent.emplace_back( two );

	mStart = zero;
	mEnd = three;
}

void EqualWeightEdgeGraph::UpdateActor( float deltaTime )
{
	if( searchComplete == false ) {
		NodeToParentMap ntpm;

		// Note we are finding the path from the end to the start.
		// If there are directed edges this will not work.
		bool found = BFS( *mGraph,  mEnd, mStart, ntpm );

		searchComplete = true;

		if( found ) {

			std::cout << "found" << std::endl;

			// Vector to hold the nodes in the path
			std::vector< const GraphNode *> pathVector;

			// Get the start node parent in the path
			const GraphNode * parent = mStart;

			// Put the start node in the vector
			pathVector.emplace_back( parent );

			while( parent != mEnd ) {

				// Get the parent in the path from start to goal
				parent = ntpm[parent];

				// Put the parent in the path vector
				pathVector.emplace_back( parent );

			}

			// Print the path
			for( auto node : pathVector ) {
				std::cout << '\t' << node->nodeName.c_str( );

			}

			std::cout << '\n';

		}
		else {
			std::cout << "not found" << std::endl;

		}
	}
}



