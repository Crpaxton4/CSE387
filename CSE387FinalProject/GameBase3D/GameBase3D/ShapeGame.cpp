#include "ShapeGame.h"

#include <iostream>

#include "Texture.h"
#include "ShapeGameActor.h"
#include "MeshComponent.h"
#include "ModelMesh.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "PositionalLightComponent.h"
#include "AmbientLightComponent.h"
#include "DirectionalLightComponent.h"
#include "SpotLightComponent.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "CylinderMesh.h"
#include "ConeMesh.h"
#include "GameBoardMesh.h"
#include "CameraComponent.h"
#include "ReparentComponent.h"
#include "SoundListenerComponent.h"
#include "SoundSourceComponent.h"
#include "SoundReverbZoneComponent.h"

ShapeGame::ShapeGame( )
	:Game( "CSE387 - Final Project")
{
}


void ShapeGame::LoadData( )
{
	// Setup lights in the scene
	ShapeGame::SetupLighting();

	//// Sun
	mSunActor = new ShapeGameActor(this);
	mSunActor->SetPosition(vec3(0, 0, -20));
	MeshComponent * sunMeshComponent = new MeshComponent(mSunActor);
	Material sunMat;
	sunMat.setDiffuseTexture(this->GetRenderer()->GetTexture("Assets/sunmap.jpg")->GetTextureObject());
	SphereMesh * sunMesh = new SphereMesh(2.0f);
	sunMesh->Load("earth sphere", sunMat);
	sunMeshComponent->SetMesh(sunMesh);

	//// Earth
	mEarthActor = new ShapeGameActor( this );
	mEarthActor->SetPosition( vec3( 10, 0, 0 ) );
	mEarthActor->SetRotation(glm::rotate(glm::radians(-90.0f), vec3(0, 1, 0)));
	MoveComponent * earthMoveComponent = new MoveComponent(mEarthActor);
	earthMoveComponent->SetAngularSpeed(glm::vec3( 0.0f, glm::radians( 1.0f ), 0.0f));
	MeshComponent * earthMeshComponent = new MeshComponent(mEarthActor);
	Material earthMat;
	earthMat.setDiffuseTexture( this->GetRenderer( )->GetTexture( "Assets/earthmap.jpg" )->GetTextureObject( ) );
	SphereMesh * earthMesh = new SphereMesh( 1.0f );
	earthMesh->Load( "earth sphere", earthMat );
	earthMeshComponent->SetMesh( earthMesh );

	//// Moon
	mMoonActor = new ShapeGameActor(this);
	MeshComponent * moonMeshComponent = new MeshComponent(mMoonActor);
	Material moonMat;
	moonMat.setDiffuseTexture(this->GetRenderer()->GetTexture("Assets/moonmap.jpg")->GetTextureObject());
	SphereMesh * moonMesh = new SphereMesh(0.25f);
	moonMesh->Load("moon sphere", moonMat);
	moonMeshComponent->SetMesh(moonMesh);
	mMoonActor->SetPosition(vec3(-2, 0, 0));
	ReparentComponent * reparentComponent = new ReparentComponent(mMoonActor, mSunActor);

	//// Empty Solar System Actor (root of the scene graph)
	ShapeGameActor * emptyActor = new ShapeGameActor(this);
	emptyActor->SetPosition(vec3(0, 0, -20));
	MoveComponent * emptyMoveComponent = new MoveComponent(emptyActor);
	emptyMoveComponent->SetAngularSpeed(glm::vec3(0.0f, glm::radians(1.0f), 0.0f));
	
	// Add actors to the scene graph
	this->AddChild(mSunActor);
	this->AddChild(emptyActor);
	emptyActor->AddChild(mEarthActor);
	mEarthActor->AddChild(mMoonActor);

	ShapeGameActor * cameraActor = new ShapeGameActor( this );
	   
	this->AddChild( cameraActor );

	cameraActor->SetPosition( vec3( 0, 0, 12 ), WORLD );

	CameraComponent * cam = new CameraComponent( cameraActor );

	this->GetRenderer( )->setActiveCamera( cam );

	//SoundListenerComponent * listComp = new SoundListenerComponent( cameraActor );

	//SoundSourceComponent * soundComp = new SoundSourceComponent( cameraActor, "Assets/Footsteps.wav",0,50 );

	//soundComp->play( true );

	//SoundReverbZoneComponent * reverb = new SoundReverbZoneComponent( cameraActor );

}

void ShapeGame::SetupLighting()
{
	//ambient light
	ShapeGameActor * ambLightActor = new ShapeGameActor( this );
	ambLightActor->SetPosition( vec3( 0.0f, 0.0f, 0.0f ) );
	AmbientLightComponent * ambLightComp = new AmbientLightComponent( ambLightActor, GL_LIGHT_ZERO, true );
	ambLightComp->setAmbientColor( vec4( 0.15f, 0.15f, 0.15f, 1.0f ) );

	//positional Light
	ShapeGameActor * posLightActor = new ShapeGameActor( this );
	posLightActor->SetPosition( vec3( 5.0f, 10.0f, -10.0f ) );
	PositionalLightComponent * posLightComp = new PositionalLightComponent( posLightActor, GL_LIGHT_ONE, false );
	posLightComp->setDiffuseColor( vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	posLightComp->setSpecularColor( vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );

	//directional Light
	ShapeGameActor * dirLightActor = new ShapeGameActor( this );
	dirLightActor->SetRotation( glm::rotate(glm::radians(45.0f), vec3(0,1,0)) * glm::rotate( glm::radians( -45.0f ), vec3( 1, 0, 0 ) ) );
	//set rotation
	DirectionalLightComponent * dirLightComp = new DirectionalLightComponent( dirLightActor, GL_LIGHT_TWO, true );
	dirLightComp->setDiffuseColor( vec4( 0.75f, 0.75f, 0.75f, 1.0f ) );
	dirLightComp->setSpecularColor( vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );

	// spot light
	ShapeGameActor *spotLightActor = new ShapeGameActor( this );
	spotLightActor->SetPosition( vec3( 0.0f, 0.0f, 0.0f ) );
	SpotLightComponent *spotLightComp = new SpotLightComponent( spotLightActor, GL_LIGHT_THREE, false );
	spotLightComp->setDiffuseColor( vec4( 0.75f, 0.75f, 0.75f, 1.0f ) );
	spotLightComp->setSpecularColor( vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	spotLightComp->setSpotCutoffCos( glm::cos( glm::radians( 10.0f ) ) );
	spotLightComp->setSpotExponent( 2 );

} // end setupLighting


