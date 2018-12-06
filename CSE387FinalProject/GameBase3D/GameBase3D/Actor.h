// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
//#include "Math.h"
#include "MathLibsConstsFuncs.h"
#include <cstdint>
#include <iostream>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const uint8_t* keyState);
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const uint8_t* keyState);

	//void SetEulerRotation(const vec3& eulerAngles) { mRotation = glm::eulerAngleXYZ( eulerAngles.x,eulerAngles.y, eulerAngles.z );  mRecomputeWorldTransform = true; }
	//vec3 GetEulerRotation( )
	//{
	//	float yaw, pitch, roll;
	//	glm::extractEulerAngleXYZ( mRotation, yaw, pitch, roll ); 
	//	return vec3( yaw, pitch, roll );
	//}

	//void SetQuaternionRotation( const quat& q ) { mRotation = glm::mat4_cast( q );  mRecomputeWorldTransform = true; }
	//quat GetQuaternionRotation( ) { return glm::quat_cast( mRotation ); }


	void SetLocalTransform(glm::mat4 transform);

	vec3 GetForward() const { return glm::mat3(mRotation) * -UNIT_Z_V3; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	Actor* GetParent() { return parent; }

	void ComputeLocalTransform();

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	
	/**
	* Gets the scale of the object relative to either the World
	* or local coordinate frame.
	* @param coordinate frame for the position
	* @returns scale relative to the specified coordinate frame.
	*/
	float GetScale(Frame frame = LOCAL);
	
	/**
	* Gets the position of the object relative to either the World
	* or local coordinate frame.
	* @param coordinate frame for the position
	* @returns position relative to the specified coordinate frame.
	*/
	glm::vec3 GetPosition(Frame frame = LOCAL);

	/**
	* Gets the orientation of the object relative to either the World
	* or local coordinate frame. Position is not changed.
	* @param coordinate frame for the rotation
	* @returns orientation relative to the specified coordinate frame.
	*/
	glm::mat4 GetRotation(Frame frame = LOCAL);
	
	/**
	* Set the position of the object relative to either the World
	* or local coordinate frame. Orientation is not changed
	* @param position vector xyz coordinates of the position
	* @param coordinate frame relative to which the position is to be set
	*/
	void SetScale(float scale, Frame frame = LOCAL);
	
	/**
	* Set the position of the object relative to either the World
	* or local coordinate frame. Orientation is not changed
	* @param position vector xyz coordinates of the position
	* @param coordinate frame relative to which the position is to be set
	*/
	void SetPosition(glm::vec3 position, Frame frame = LOCAL);

	/**
	* Set the orientation of the object relative to either the World
	* or local coordinate frame. Position is not changed.
	* @param rotation 3 x 3 matrix describing the orientation
	* @param coordinate frame relative to which the rotation is to be set
	*/
	void SetRotation(glm::mat4 rotation, Frame frame = LOCAL);

	/**
	* Returns the facing direction of the object relative to either the Local
	* or World coordinate frame
	* @param coordinate frame for the facing direction
	* @returns facing direction relative to the specified coordinate frame.
	*/
	glm::vec3 GetFacingDirection(Frame frame = LOCAL);

	/**
	* Returns the up direction of the object relative to either the Local
	* or World coordinate frame
	* @param coordinate frame for the up direction
	* @returns up direction relative to the specified coordinate frame.
	*/
	glm::vec3 GetUpDirection(Frame frame = LOCAL);

	/**
	* Remove a child of this Actor scene graph node. Parent of the
	* child is set to nullptr.
	* @param child - child that is being removed
	*/
	void removeChild( Actor * child );

	/**
	* Adds a child to this Actor. Removes the child
	* from the children of the former parent. Local transformation is set
	* so that the position and orientation relative to the World reference
	* frame is unchanged. Set the parent of the child to "this" Actor.
	* @param child - child that is being added
	*/
	void Reparent( Actor * child );

	/**
	* Detaches "this" Actor scene graph node from its parent. Parent
	* is set to nullptr.
	*/
	void DetachFromParent( );

	/**
	* Add a child to this scene graph node. Set the parent of
	* the child to "this."  Modeling transformation of the
	* child is unchanged.
	* @param Actor child that is being added as a child
	*/
	void AddChild( Actor * child );

	/**
	* Returns the World transformation of the parent of this VisibleObject
	* scene graph node
	* @return World transformation of the parent of this node
	*/
	glm::mat4 GetParentWorldTransform( );

	/**
	* Returns the Local transformation this VisibleObject
	* scene graph node
	* @return Local transformation of the parent of this node
	*/
	glm::mat4 GetLocalTransformation( );

	/**
	* Returns the World transformation of this VisibleObject
	* scene graph node.
	* @return World transformation of this node
	*/
	glm::mat4 GetWorldTransformation( );

protected:
	// Actor's state
	State mState;

	// Transform
	mat4 mLocalTransform;

	/*
	orien orien orien pos
	orien orien orien pos
	orien orien orien pos
	x     x     x     pos
	
	*/

	// Local position, scale, and rotation;
	vec3 mPosition;
	float mScale;
	mat4 mRotation;
//	bool mRecomputeWorldTransform;
	bool mRecomputeLocalTransform;

	std::vector<class Component*> mComponents;

	// Children of this Actor in the scene graph
	std::vector<Actor *> children;

	// Reference to parent in the scene graph
	Actor * parent = nullptr;

	class Game* mGame;
};
