#include "MyMultiActor.h"

#include "Game.h"



MyMultiActor::MyMultiActor( Game* game )
	:Actor( game )
{
	// Create an animated sprite component
	masc = new MultiAnimSpriteComponent( this );

	std::vector<SDL_Texture*> animation1 = {
		game->GetTexture( "Assets/Character01.png" ),
		game->GetTexture( "Assets/Character02.png" ),
		game->GetTexture( "Assets/Character03.png" ),
		game->GetTexture( "Assets/Character04.png" ),
		game->GetTexture( "Assets/Character05.png" ),
		game->GetTexture( "Assets/Character06.png" ),
	};
	
	masc->AddAnimation("walk", animation1);

	std::vector<SDL_Texture*> animation2 = {
		game->GetTexture( "Assets/Enemy01.png" ),
		game->GetTexture( "Assets/Enemy02.png" ),
		game->GetTexture( "Assets/Enemy03.png" ),
		game->GetTexture( "Assets/Enemy04.png" ),
		game->GetTexture( "Assets/Enemy05.png" ),
		game->GetTexture( "Assets/Enemy06.png" ),

	};
	masc->AddAnimation( "enemy", animation2 );

	masc->SetAnimFPS( 12.0f );

	masc->PlayAnimation( "enemy" );
}

void MyMultiActor::ActorInput( const uint8_t* keyState )
{
	if( keyState[SDL_SCANCODE_E]  ) {

		masc->PlayAnimation( "enemy" );

	}
	else if( keyState[SDL_SCANCODE_W] ) {

		masc->PlayAnimation( "walk" );

	}
}



