#include "CameraComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include <SDL/SDL.h>
#include "SharedProjectionAndViewing.h"

std::vector<CameraComponent*> CameraComponent::activeCameras;

CameraComponent::CameraComponent( class Actor* owner, int updateOrder )
	:Component( owner )
{
}

/**
* Called before the scene is rendered from the perspective of this camera.
* Sets the viewport, projection matrix, and viewing transformation based upon this Camera so
* that the scene can be rendered in the specified viewport without distortion from the
* viewpoint of the Camera. Uses methods of the SharedProjectionAndViewing class to accomplish
* this task.
*/
void CameraComponent::setViewingTransformation( )
{
	int width, height;
	// Get the current width and height of the rendering window
	width = mOwner->GetGame( )->GetRenderer( )->GetScreenWidth( );
	height = mOwner->GetGame( )->GetRenderer( )->GetScreenHeight( );

	glViewport( static_cast<GLint>(xLowerLeft * width), static_cast<GLint>( yLowerLeft * height),
				static_cast<GLint>( viewPortWidth * width ), static_cast<GLint>( viewPortHeight * height) );

	SharedProjectionAndViewing::setViewMatrix( glm::inverse(mOwner->GetWorldTransformation()) );

	GLfloat aspect = static_cast<float>(viewPortWidth * width) / (viewPortHeight * height); // This needs to be changed to used the dimensions of the viewport and

	mat4 projMat = glm::perspective( glm::radians( 45.0f ), aspect, 1.0f, 200.0f );

	SharedProjectionAndViewing::setProjectionMatrix( projMat );
}

/**
* Sets the rendering area for the camera. In normalized coordinate the width and height
* of the viewport are 1.0.
	*
	* @param xLowerLeft normalized x coordinate of the lower left hand corner or the viewport
	* @param yLowerLeft normalized y coordinate of the lower left hand corner or the viewport
	* @param viewPortWidth normalized width of the view port in pixels
	* @param viewPortHeight normalized height of the view port in pixels
	*/
void CameraComponent::setViewPort( GLfloat xLowerLeft, GLfloat yLowerLeft, GLfloat viewPortWidth, GLfloat viewPortHeight )
{
	this->xLowerLeft = xLowerLeft;
	this->yLowerLeft = yLowerLeft;
	this->viewPortWidth = viewPortWidth;
	this->viewPortHeight = viewPortHeight;
}