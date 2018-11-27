#include "ShapeGameActor.h"
#include "ShapeGame.h"

ShapeGameActor::ShapeGameActor( ShapeGame* game )
	:Actor( game )
{
}

class ShapeGame* ShapeGameActor::GetShapeGame( )
{
	return static_cast<ShapeGame*>( GetGame( ) );

}
