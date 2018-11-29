#pragma once
#include "Component.h"


#include <iostream>

// Physics
#include "PhysicsEngine.h"


struct CollisionData;

class RigidBodyComponent : 	public Component, public btMotionState
{
	public:
	RigidBodyComponent( class Actor* owner, class MeshComponent * mesh, DynamicsState state = DYNAMIC, int updateOrder = 100 );

	virtual ~RigidBodyComponent( );

	// Called by bullet to get the position and orientation of the object
	virtual void getWorldTransform( btTransform &worldTrans ) const;

	// Callled by bullet to set the position and orientation of the object
	virtual void setWorldTransform( const btTransform &worldTrans );

	void CollisionEnter( const RigidBodyComponent * collisionData ) const { std::cout << "CollisionEnter" << std::endl; }

	void CollisionExit( const RigidBodyComponent * collisionData ) const { std::cout << "CollisionExit" << std::endl; }



	protected:

	class btRigidBody * bulletRigidBody = nullptr;

	class btCollisionShape *  bulletCollisionShape;

	class btTransform bulletTransform;

	DynamicsState rigidbodyDynamics = NONE;


};

