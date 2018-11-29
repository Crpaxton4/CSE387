#include "RigidBodyComponent.h"

#include "Actor.h"
#include "MeshComponent.h"

RigidBodyComponent::RigidBodyComponent( Actor* owner, MeshComponent * mesh, DynamicsState state, int updateOrder)
	: Component( owner, updateOrder )
{
	this->rigidbodyDynamics = state;

	float scale = owner->GetScale( WORLD );

	this->bulletCollisionShape = mesh->GetCollisionShape( );

	this->bulletCollisionShape->setLocalScaling( btVector3( scale, scale, scale ) );

	if( this->rigidbodyDynamics == DYNAMIC ) {

		// Object staring with no inertia.
		btScalar mass = 1;
		btVector3 inertia( 0, 0, 0 );
		bulletCollisionShape->calculateLocalInertia( mass, inertia );

		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			mass,							// mass SHOULD BE NON-ZERO FOR DYNAMIC RIGIDBODIES
			this ,							// motion state
			bulletCollisionShape,			// collision shape of body
			inertia							// local inertia
		);

		this->bulletRigidBody = new btRigidBody( rigidBodyCI );

		PhysicsEngine::dynamicsWorld->addRigidBody( bulletRigidBody );

	}
	else if( this->rigidbodyDynamics == KINEMATIC_MOVING || this->rigidbodyDynamics == KINEMATIC_STATIONARY ) {

		// Static object with no inertia.
		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			0,							// mass SHOULD BE ZERO FOR KINEMATIC RIGIDBODIES
			this,						// motion state
			bulletCollisionShape,		// collision shape of body
			btVector3( 0, 0, 0 )		// local inertia
		);

		this->bulletRigidBody = new btRigidBody( rigidBodyCI );

		if( this->rigidbodyDynamics == KINEMATIC_MOVING ) {
			bulletRigidBody->setCollisionFlags( bulletRigidBody->getCollisionFlags( ) | btCollisionObject::CF_KINEMATIC_OBJECT );
			bulletRigidBody->setActivationState( DISABLE_DEACTIVATION );
		}
		else {

			bulletRigidBody->setCollisionFlags( bulletRigidBody->getCollisionFlags( ) | btCollisionObject::CF_STATIC_OBJECT );
		}

		PhysicsEngine::dynamicsWorld->addRigidBody( bulletRigidBody );
	}
	else {
		this->bulletRigidBody = nullptr;
		this->bulletCollisionShape = nullptr;
	}

}

RigidBodyComponent::~RigidBodyComponent( )
{
	if( bulletRigidBody != nullptr && PhysicsEngine::dynamicsWorld != nullptr ) {
		PhysicsEngine::dynamicsWorld->removeRigidBody( bulletRigidBody );
		//_aligned_free(bulletRigidBody->getMotionState()); // May be an error source on shutdown
	}
}

// Called by bullet to get the position and orientation of the object
void RigidBodyComponent::getWorldTransform( btTransform &worldTrans ) const
{

	// Calculate current world transformation and set world trans to it 
	worldTrans = PhysicsEngine::convertTransform( mOwner->GetWorldTransformation( ) );

	std::cout << "RigidBodyComponent::getWorldTransform" << std::endl;
}

// Callled by bullet to set the position and orient the object
void RigidBodyComponent::setWorldTransform( const btTransform &worldTrans )
{
		bulletTransform = worldTrans;

		glm::mat4 T = PhysicsEngine::convertTransform( worldTrans );

		mOwner->SetLocalTransform( glm::inverse( mOwner->GetParentWorldTransform( ) ) * T );

		//std::cout << "RigidBodyComponent::setWorldTransform" << std::endl;
}


