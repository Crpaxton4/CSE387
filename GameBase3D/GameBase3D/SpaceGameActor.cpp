#include "SpaceGameActor.h"
#include "SpaceGame.h"

SpaceGameActor::SpaceGameActor( SpaceGame* game )
	:Actor( game )
{
}

class SpaceGame* SpaceGameActor::GetSpaceGame( )
{
	return static_cast<SpaceGame*>( GetGame( ) );

}
