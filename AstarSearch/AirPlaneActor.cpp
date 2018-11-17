#include "AirPlaneActor.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"



AirPlaneActor::AirPlaneActor( class Game* game )
	:Actor(game )
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent( this );
	sc->SetTexture( game->GetTexture( "Assets/Airplane.png" ) );

	MoveComponent * mc = new MoveComponent( this );

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent( this );
	ic->SetForwardKey( SDL_SCANCODE_W );
	ic->SetBackKey( SDL_SCANCODE_S );
	ic->SetClockwiseKey( SDL_SCANCODE_A );
	ic->SetCounterClockwiseKey( SDL_SCANCODE_D );
	ic->SetMaxForwardSpeed( 300.0f );
	ic->SetMaxAngularSpeed( TWO_PI );

}



