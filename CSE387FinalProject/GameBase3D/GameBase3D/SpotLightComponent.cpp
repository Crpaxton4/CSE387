#include "SpotLightComponent.h"
#include "Game.h"
#include "Actor.h"
SpotLightComponent::SpotLightComponent( class Actor* owner, lightSource id, bool enabled ) 
	:LightComponent( owner, id, enabled )
{
	SharedGeneralLighting::setIsSpot( id, true );

	OnUpdateWorldTransform( );
}


void SpotLightComponent::setSpotCutoffCos( float cosine )
{
	SharedGeneralLighting::setSpotCutoffCos( id, cosine );
}
void SpotLightComponent::setSpotExponent( float ex )
{
	SharedGeneralLighting::setSpotExponent( id, ex );
}

void SpotLightComponent::OnUpdateWorldTransform( )
{
	SharedGeneralLighting::setPositionOrDirection( id, vec4( mOwner->GetPosition( WORLD ), 1.0f ) );

	SharedGeneralLighting::setSpotDirection( id, mOwner->GetFacingDirection(WORLD) );
}

void SpotLightComponent::ProcessInput( const uint8_t* keyState )
{

	if( keyState[SDL_SCANCODE_S] ) {
	
		SharedGeneralLighting::setEnabled( id, !SharedGeneralLighting::getEnabled( id ) );

	}
}