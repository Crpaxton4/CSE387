#include "ShapeGame.h"

#include <iostream>

#include "Texture.h"
#include "ShapeGameActor.h"
#include "MeshComponent.h"
#include "ModelMesh.h"
#include "Renderer.h"
#include "SpriteComponent.h"
//#include "MoveComponent.h"
#include "SharedGeneralLighting.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "CylinderMesh.h"
#include "ConeMesh.h"
#include "GameBoardMesh.h"
#include "ReparentComponent.h"

ShapeGame::ShapeGame( )
	:Game( "CSE387 - Project 2")
{
}


void ShapeGame::LoadData( )
{
	// Sun
	mSunActor = new ShapeGameActor(this);
	mSunActor->SetPosition(vec3(0, 0, -20));
	MeshComponent * sunMeshComponent = new MeshComponent(mSunActor);
	Material sunMat;
	sunMat.setDiffuseTexture(this->GetRenderer()->GetTexture("Assets/sunmap.jpg")->GetTextureObject());
	SphereMesh * sunMesh = new SphereMesh(2.0f);
	sunMesh->Load("sun sphere", sunMat);
	sunMeshComponent->SetMesh(sunMesh);

	// Earth
	mEarthActor = new ShapeGameActor( this );
	mEarthActor->SetPosition( vec3( 10, 0, 0 ) );


	MeshComponent * earthMeshComponent = new MeshComponent(mEarthActor);
	Material earthMat;
	earthMat.setDiffuseTexture( this->GetRenderer( )->GetTexture( "Assets/earthmap.jpg" )->GetTextureObject( ) );
	SphereMesh * earthMesh = new SphereMesh( 1.0f );
	earthMesh->Load( "earth sphere", earthMat );
	earthMeshComponent->SetMesh( earthMesh );

	// Moon
	mMoonActor = new ShapeGameActor(this);
	MeshComponent * moonMeshComponent = new MeshComponent(mMoonActor);
	Material moonMat;
	moonMat.setDiffuseTexture(this->GetRenderer()->GetTexture("Assets/moonmap.jpg")->GetTextureObject());
	SphereMesh * moonMesh = new SphereMesh(0.25f);
	moonMesh->Load("moon sphere", moonMat);
	moonMeshComponent->SetMesh(moonMesh);
	mMoonActor->SetPosition(vec3(-2, 0, 0));


	ReparentComponent * reparentComponent = new ReparentComponent(mMoonActor, mSunActor);

	// Empty Solar System Actor (root of the scene graph)
	ShapeGameActor * emptyActor = new ShapeGameActor(this);
	emptyActor->SetPosition(vec3(0, 0, -20));
	
	// Add actors to the scene graph
	this->AddActor(mSunActor);
	this->AddActor(emptyActor);
	emptyActor->AddChild(mEarthActor);
	mEarthActor->AddChild(mMoonActor);
}



