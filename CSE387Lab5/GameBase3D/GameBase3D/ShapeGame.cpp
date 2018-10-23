#include "ShapeGame.h"

#include <iostream>

#include "Texture.h"
#include "ShapeGameActor.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

ShapeGame::ShapeGame( )
	:Game( "CSE387 - ShapeGame")
{
}


void ShapeGame::LoadData( )
{
	//// shape code

	//ShapeGameActor * shape = new ShapeGameActor( this );
	//shape->SetPosition( vec3( 0, 0, -12 ) );
	//shape->SetRotation( vec3( 0.0f, 0.0f, 0.0 ) );
	//
	//MoveComponent * mc = new MoveComponent( shape );

	//mc->SetForwardSpeed( 5.0f );
	//mc->SetAngularSpeed( vec3(0.0f, 0.0f, glm::radians( 25.0f ) ));

	//Mesh * defaultMesh = new Mesh();

	//defaultMesh->SetTexture( this->GetRenderer( )->GetTexture( "Assets/Ship.png" ));

	//defaultMesh->Load( this->GetRenderer( ) );

	//MeshComponent * shapeMeshComponent = new MeshComponent( shape );

	//shapeMeshComponent->SetMesh( defaultMesh );

	//shape->AddComponent( shapeMeshComponent );

	//// sprite Actor Code

	//ShapeGameActor * spriteActor = new ShapeGameActor( this );

	//spriteActor->SetPosition( vec3( 100, 100, 0 ) );

	//SpriteComponent * spriteComp = new SpriteComponent( spriteActor );

	//Texture * spriteText = this->GetRenderer( )->GetTexture( "Assets/asteroid.png" );

	//spriteComp->SetTexture( spriteText );

}


