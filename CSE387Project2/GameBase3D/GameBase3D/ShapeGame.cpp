#include "ShapeGame.h"

#include <iostream>

#include "Texture.h"
#include "ShapeGameActor.h"
#include "MeshComponent.h"
#include "ModelMesh.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "SharedGeneralLighting.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "CylinderMesh.h"
#include "ConeMesh.h"
#include "GameBoardMesh.h"
#include "PlaneMesh.h"
#include "LightComponent.h"

ShapeGame::ShapeGame( )
	:Game( "CSE387 - Project 2")
{
}


void ShapeGame::LoadData( )
{
	// Setup lights in the scene
	ShapeGame::SetupLighting();

	// Model
	ShapeGameActor * modelActor = new ShapeGameActor( this );
	modelActor->SetPosition( vec3( -1, -3, -8) );
	modelActor->SetRotation( glm::rotate( glm::radians( -90.0f ), vec3( 0, 1, 0 ) ) );
	modelActor->SetScale(.8f);
	
	// Make the model spin
	// Use for debugging
	MoveComponent * mc = new MoveComponent( modelActor );
	mc->SetAngularSpeed(glm::vec3( 0.0f, glm::radians( 1.0f ), 0.0f));

	ModelMesh * modelMesh = new ModelMesh();

	modelMesh->Load(this->GetRenderer(), "Assets/Dinosaur/Trex.obj");

	MeshComponent * modelMeshComponent = new MeshComponent( modelActor );

	modelMeshComponent->SetMesh( modelMesh );

	//// Gameboard
	//ShapeGameActor * gbActor = new ShapeGameActor( this );
	//gbActor->SetPosition( vec3( 0, -3, 0 ) );

	//MeshComponent * gbComponent = new MeshComponent( gbActor );

	//Material dark;
	//dark.setAmbientAndDiffuseMat( vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );

	//Material light;
	//light.setAmbientAndDiffuseMat( vec4( 0.9f, 0.9f, 0.9f, 1.0f ) );

	//GameBoardMesh* boardMesh = new GameBoardMesh( );
	//boardMesh->Load( "board", dark, light );

	//gbComponent->SetMesh( boardMesh );

	//// Earth
	//ShapeGameActor * sphereActor = new ShapeGameActor( this );
	//sphereActor->SetPosition( vec3( 3, -1.5, 0 ) );
	//sphereActor->SetRotation( glm::rotate( glm::radians( -90.0f ), vec3( 0, 1, 0 ) ) );

	//MeshComponent * sphereMeshComponent = new MeshComponent( sphereActor );

	//Material earthMat;
	//earthMat.setDiffuseTexture( this->GetRenderer( )->GetTexture( "Assets/earthmap.jpg" )->GetTextureObject( ) );

	//SphereMesh * sphereMesh = new SphereMesh( 1.0f );
	//sphereMesh->Load( "earth sphere", earthMat );

	//sphereMeshComponent->SetMesh( sphereMesh );

	//// Cone
	//ShapeGameActor * coneActor = new ShapeGameActor( this );
	//coneActor->SetPosition( vec3( 3.5, -3, 2.5 ) );
	//coneActor->SetRotation( glm::rotate( glm::radians( -90.0f ), vec3( 1, 0, 0 ) ) );

	//MeshComponent * coneComponent = new MeshComponent( coneActor );

	//Material coneMat;
	//coneMat.setAmbientAndDiffuseMat( vec4( 1, 1, 0, 1 ) );

	//ConeMesh * coneMesh = new ConeMesh(  );
	//coneMesh->Load( "cone", coneMat );

	//coneComponent->SetMesh( coneMesh );

	//// Cylinder
	//ShapeGameActor * cylinderActor = new ShapeGameActor( this );
	//cylinderActor->SetPosition( vec3( -2, -3, 0 ) );
	//cylinderActor->SetRotation( glm::rotate( glm::radians( -90.0f ), vec3( 1, 0, 0 ) ) );

	//MeshComponent * cylinderComponent = new MeshComponent( cylinderActor );

	//Material cylinderMat;
	//cylinderMat.setAmbientAndDiffuseMat( vec4( 1, 0, 0, 1 ) );

	//CylinderMesh * cylinderMesh = new CylinderMesh( );
	//cylinderMesh->Load( "cylinder", cylinderMat );

	//cylinderComponent->SetMesh( cylinderMesh );

	//// Box
	//ShapeGameActor * cubeActor = new ShapeGameActor( this );
	//cubeActor->SetPosition( vec3( -3, -2, 2.5 ) );

	//MeshComponent * cubeComponent = new MeshComponent( cubeActor );

	//Material cubeMat;
	//cubeMat.setAmbientAndDiffuseMat( vec4( 0, 0, 1, 1 ) );

	//CubeMesh * cubeMesh = new CubeMesh( 1, 2, 3);
	//cubeMesh->Load( "cube", cubeMat );

	//cubeComponent->SetMesh( cubeMesh );


	//// Wall Plane
	//ShapeGameActor* wallPlaneActor = new ShapeGameActor(this);
	//wallPlaneActor->SetPosition(vec3(0.0f, 0.0f, -4.0f));

	//MeshComponent* wallCompoment = new MeshComponent(wallPlaneActor);

	//PlaneMesh* planeMesh = new PlaneMesh(8.0f, 6.0f);

	//Material planeMat;
	//planeMat.setAmbientAndDiffuseMat(vec4(1.0f, 0.5f, 0.5f, 1.0f));

	//planeMat.setDiffuseTexture(this->GetRenderer()->GetTexture("Assets/brick.bmp")->GetTextureObject());

	//
	//planeMesh->Load("plane", planeMat);

	//wallCompoment->SetMesh(planeMesh);

}

void ShapeGame::ProcessInput() {
	SDL_Event event;

	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_WINDOWEVENT) { // Windows event?

			switch (event.window.event) {

			case SDL_WINDOWEVENT_SIZE_CHANGED:

				mRenderer->Resize();

				break;
			}
		}
		else {

			switch (event.type) {

				// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				std::cout << "Window closed. Quitting." << std::endl;
				mIsRunning = false;
				break;

			case SDL_KEYDOWN:
				
				if (keyState[SDL_SCANCODE_ESCAPE])
				{
					mIsRunning = false;
				}

				if (keyState[SDL_SCANCODE_A])
				{
					ambL->toggle();
				}

				if (keyState[SDL_SCANCODE_P])
				{
					posL->toggle();
				}

				if (keyState[SDL_SCANCODE_D])
				{
					dirL->toggle();
				}

				if (keyState[SDL_SCANCODE_S])
				{
					spotL->toggle();
				}

				

			}
		}
	}

	
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void ShapeGame::SetupLighting()
{

	//// Create ambient light actor
	Actor* ambientLight = new Actor(this);
	ambL = new LightComponent(ambientLight, 0);
	ambL->setEnabled(true);
	ambL->setAmbient(vec4(0.15f, 0.15f, 0.15f, 1.0f));
	
	Actor* positionalLight = new Actor(this);
	posL = new LightComponent(positionalLight, 1);
	posL->setEnabled(true);
	posL->setDiffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	posL->setSpecular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	posL->setPositional(vec3(5.0f, 10.0f, -10.0f));

	Actor* directionalLight = new Actor(this);
	dirL = new LightComponent(directionalLight, 2);
	dirL->setEnabled(true);
	dirL->setDiffuse(vec4(0.75f, 0.75f, 0.75f, 1.0f));
	dirL->setSpecular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	dirL->setDirectional(vec3(1.0f, 1.0f, 1.0f));

	Actor* spotLight = new Actor(this);
	spotL = new LightComponent(spotLight, 3);
	spotL->setEnabled(true);
	spotL->makeSpotlight(vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 6.0f, -6.0f), 0.999f, 1.0f);
	spotL->setSpecular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	spotL->setDiffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//// ***** Ambient Light **************
	//SharedGeneralLighting::setEnabled(GL_LIGHT_ZERO, false);
	//SharedGeneralLighting::setAmbientColor( GL_LIGHT_ZERO, vec4(0.15f, 0.15f, 0.15f, 1.0f));

	//// ***** Positional Light ***************
	//SharedGeneralLighting::setEnabled(GL_LIGHT_ONE, false);
	//SharedGeneralLighting::setDiffuseColor(GL_LIGHT_ONE, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//SharedGeneralLighting::setSpecularColor(GL_LIGHT_ONE, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//SharedGeneralLighting::setPositionOrDirection(GL_LIGHT_ONE, vec4(5.0f, 10.0f, -10.0f, 1.0f));

	//// ***** Directional Light ***************
	//SharedGeneralLighting::setEnabled(GL_LIGHT_TWO, false);
	//SharedGeneralLighting::setDiffuseColor(GL_LIGHT_TWO, vec4(0.75f, 0.75f, 0.75f, 1.0f));
	//SharedGeneralLighting::setSpecularColor(GL_LIGHT_TWO, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//SharedGeneralLighting::setPositionOrDirection(GL_LIGHT_TWO, vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//spot
	//SharedGeneralLighting::setEnabled(GL_LIGHT_THREE, true);
	//SharedGeneralLighting::setIsSpot(GL_LIGHT_THREE, true);
	//SharedGeneralLighting::setSpotDirection(GL_LIGHT_THREE, vec3(0.0f, 0.0f, -1.0f));
	//SharedGeneralLighting::setPositionOrDirection(GL_LIGHT_THREE, vec4(0.0f, 0.0f, 0.0f, 1.0f));
	//SharedGeneralLighting::setSpotCutoffCos(GL_LIGHT_THREE, 0.8f);
	//SharedGeneralLighting::setSpotExponent(GL_LIGHT_THREE, 1.0f);
	//SharedGeneralLighting::setDiffuseColor(GL_LIGHT_THREE, vec4(0.75f, 0.75f, 0.75f, 1.0f));
	//SharedGeneralLighting::setSpecularColor(GL_LIGHT_THREE, vec4(1.0f, 1.0f, 1.0f, 1.0f));


} // end setupLighting


