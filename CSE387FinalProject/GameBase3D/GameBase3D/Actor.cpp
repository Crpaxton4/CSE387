// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>
#include <glm/gtx/matrix_decompose.hpp>

Actor::Actor( Game* game )
	:mState( EActive )
	, mPosition( ZERO_V3 )
	, mScale( 1.0f )
	, mRotation( mat4( 1.0 ) )
	, mGame( game )
	, mRecomputeLocalTransform( true )
{

}

Actor::~Actor( )
{
	mGame->RemoveActor( this );

	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while( !mComponents.empty( ) ) {
		delete mComponents.back( );
	}

	// Delete all children
	for( Actor * child : children ) {
		delete child;
	}
}

void Actor::Update( float deltaTime )
{
	if( mState == EActive ) {
		ComputeLocalTransform( );

		UpdateComponents( deltaTime );
		UpdateActor( deltaTime );

		ComputeLocalTransform( );

		// Update all children
		for( Actor * child : children ) {
			child->Update( deltaTime );
		}
	}
}

void Actor::UpdateComponents( float deltaTime )
{
	for( auto comp : mComponents ) {
		comp->Update( deltaTime );
	}

}

void Actor::UpdateActor( float deltaTime )
{
}

void Actor::ProcessInput( const uint8_t* keyState )
{
	if( mState == EActive ) {
		// First process input for components
		for( auto comp : mComponents ) {
			comp->ProcessInput( keyState );
		}

		ActorInput( keyState );

		// Process input for children
		for( Actor * child : children ) {
			child->ProcessInput( keyState );
		}
	}
}

void Actor::ActorInput( const uint8_t* keyState )
{
}

void Actor::SetLocalTransform( glm::mat4 transform )
{
	this->mRecomputeLocalTransform = true;
	ComputeLocalTransform( );

	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose( transform, scale, rotation, translation, skew, perspective );

	//mScale = ( scale.x + scale.y + scale.z ) / 3.0f;
	mPosition = translation;
	mRotation = glm::toMat4( rotation );

	this->mRecomputeLocalTransform = true;
	ComputeLocalTransform( );
}

void Actor::ComputeLocalTransform( )
{
	if( mRecomputeLocalTransform ) {
		mRecomputeLocalTransform = false;

		// Translate, rotate, and scale
		mLocalTransform =
			glm::translate( mPosition ) *
			mRotation *
			glm::scale( vec3( mScale, mScale, mScale ) );

		// Inform components world transform updated
		for( auto comp : mComponents ) {
			comp->OnUpdateLocalTransform( );
		}
	}
}

void Actor::AddComponent( Component* component )
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder( );
	auto iter = mComponents.begin( );
	for( ;
		iter != mComponents.end( );
		++iter ) {
		if( myOrder < ( *iter )->GetUpdateOrder( ) ) {
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert( iter, component );
}

void Actor::RemoveComponent( Component* component )
{
	auto iter = std::find( mComponents.begin( ), mComponents.end( ), component );
	if( iter != mComponents.end( ) ) {
		mComponents.erase( iter );
	}
}

float Actor::GetScale( Frame frame )
{
	return mScale;
	//if( frame == Frame::LOCAL ) {
	//	// Get the scale in local coordinates
	//	return mScale;
	//}
	//else {
	//	// Get the scale in world coordinates
	//	float localScale = mScale;
	//	if( this->parent == nullptr ) {
	//		return localScale;
	//	}
	//	else {
	//		return this->parent->GetScale( frame ) * localScale;
	//	}
	//}
}

glm::vec3 Actor::GetPosition( Frame frame )
{
	glm::vec3 position;
	if( frame == Frame::LOCAL ) {
		// Get the position in local coordinates
		position = mPosition;
	}
	else {
		// Get the position in world coordinates
		glm::vec4 worldPosition = GetParentWorldTransform( ) * glm::vec4( mPosition, 1.0f );
		position = glm::vec3( worldPosition );
	}
	return position;
}

glm::mat4 Actor::GetRotation( Frame frame )
{
	if( frame == Frame::LOCAL ) {
		// Get the rotation in local coordinates
		return mRotation;
	}
	else {
		// Get the rotation in world coordinates
		glm::mat4 localRotation = mRotation;
		if( this->parent == nullptr ) {
			return localRotation;
		}
		else {
			return this->parent->GetRotation( frame ) * localRotation;
		}
	}
}

void Actor::SetScale( float scale, Frame frame )
{
	mRecomputeLocalTransform = true;

	mScale = scale;

	//if( frame == Frame::LOCAL ) {
	//	mScale = scale;
	//}
	//else {
	//	if( this->parent == nullptr ) {
	//		mScale = scale;
	//	}
	//	else {
	//		float parentWorldScale = this->parent->GetScale( Frame::WORLD );
	//		float parentWorldScaleInverse = 1.0f / parentWorldScale;
	//		mScale = parentWorldScaleInverse * scale;
	//	}
	//}

	ComputeLocalTransform( );
}

void Actor::SetPosition( glm::vec3 position, Frame frame )
{
	mRecomputeLocalTransform = true;
	if( frame == Frame::LOCAL ) {
		// Set the position in local coordinates
		mPosition = position;
	}
	else {
		// Set the position in world coordinates
		glm::vec4 worldPosition = glm::vec4( position, 1.0f );
		mPosition = glm::inverse( GetParentWorldTransform( ) ) * worldPosition;
	}

	ComputeLocalTransform( );
}

void Actor::SetRotation( glm::mat4 rotation, Frame frame )
{
	mRecomputeLocalTransform = true;
	if( frame == Frame::LOCAL ) {
		// Set the rotation in local coordinates
		mRotation = rotation;
	}
	else {
		// Set the rotation in world coordinates
		if( this->parent == nullptr ) {
			mRotation = rotation;
		}
		else {
			glm::mat4 parentWorldRotation = this->parent->GetRotation( Frame::WORLD );
			mRotation = glm::inverse( parentWorldRotation ) * rotation;
		}
	}
}

glm::vec3 Actor::GetFacingDirection( Frame frame )
{
	if( frame == Frame::LOCAL ) {
		return FORWARD;
	}
	else {
		return glm::mat3( GetRotation( frame ) ) * FORWARD;
	}
}


void Actor::AddChild( Actor *  child )
{
	children.push_back( child );
	child->parent = this;
}



glm::mat4 Actor::GetParentWorldTransform( )
{
	if( parent == nullptr ) {

		return mat4( 1.0f );
	}
	else {
		return parent->GetWorldTransformation( );
	}
}


glm::mat4 Actor::GetLocalTransformation( )
{
	return mLocalTransform;
}


glm::mat4 Actor::GetWorldTransformation( )
{
	return GetParentWorldTransform( ) * mLocalTransform;
}

glm::vec3 Actor::GetUpDirection( Frame frame )
{
	if( frame == Frame::LOCAL ) {
		return UP;
	}
	else {
		return glm::mat3( GetRotation( frame ) ) * UP;
	}
}

void Actor::removeChild( Actor *  child )
{
	auto iter = std::find( children.begin( ), children.end( ), child );
	if( iter != children.end( ) ) {

		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap( iter, children.end( ) - 1 );
		children.pop_back( );
	}


} // end removeChild


void Actor::Reparent( Actor * child )
{
	glm::mat4 oldWorldTransformation = child->GetWorldTransformation( );

	child->DetachFromParent( );

	AddChild( child );

	// Get world of the new parent world traformation and old child world transform
	glm::mat4 newTransform = glm::inverse( this->GetWorldTransformation( ) ) * oldWorldTransformation;

	// Overwrite the position scale and rotation 
	child->SetLocalTransform( newTransform );

} // end reparent


void Actor::DetachFromParent( )
{
	if( parent != nullptr ) {

		auto iter = std::find( parent->children.begin( ), parent->children.end( ), this );
		if( iter != parent->children.end( ) ) {

			// Swap to end of vector and pop off (avoid erase copies)
			std::iter_swap( iter, parent->children.end( ) - 1 );
			parent->children.pop_back( );
		}
	}

} // end detachFromParent