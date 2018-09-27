#include "Guard.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Random.h"
#include "PhysicalMovementComponent.h"
#include "Game.h"
#include "GuardAIComponent.h"
#include "AIState.h"
#include "MoveComponent.h"


GuardActor::GuardActor( Game* game )
	:Actor( game )
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent( this );
	sc->SetTexture( game->GetTexture( "Assets/canonBall.png" ) );

	SetPosition( Random::GetVector( ZERO_V2, vec2( 1084, 768 ) ) );

	MoveComponent * mc = new MoveComponent( this );

	AIComponent * aic = new GuardAIComponent( this );
	// Register states with AIComponent
	aic->RegisterState( new AIPatrol( aic ) );
	aic->RegisterState( new AIDeath( aic ) );
	aic->RegisterState( new AIAttack( aic ) );
	// Start in patrol state
	aic->ChangeState( "Patrol" );

}



