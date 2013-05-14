/*
 * GFXPhysicWorld.cpp
 *
 *  Created on: 2013/05/06
 *      Author: yoshi
 */

#include "GFXPhysicWorld.h"

namespace gfxe
{

GFXPhysicWorld::GFXPhysicWorld()
{
}

GFXPhysicWorld::~GFXPhysicWorld()
{
    if( _softRigidDynamicsWorld ) {
        while( _softRigidDynamicsWorld->getNumCollisionObjects() )
        {
            btCollisionObject *btcollisionobject = _softRigidDynamicsWorld->getCollisionObjectArray()[ 0 ];
            btRigidBody *btrigidbody = btRigidBody::upcast( btcollisionobject );

            if( btrigidbody )
            {
                delete btrigidbody->getCollisionShape();
                delete btrigidbody->getMotionState();

                _softRigidDynamicsWorld->removeRigidBody( btrigidbody );
                _softRigidDynamicsWorld->removeCollisionObject( btcollisionobject );

                delete btrigidbody;
            }
        }

        delete _collisionConfig;
        delete _collisionDispatcher;
        delete _broadphaseInterface;
        delete _constraintSolver;
        delete _softRigidDynamicsWorld;
    }
}

void GFXPhysicWorld::initialize()
{
    _collisionConfig = new btSoftBodyRigidBodyCollisionConfiguration();

    _collisionDispatcher = new btCollisionDispatcher( _collisionConfig );

    _broadphaseInterface = new btDbvtBroadphase();

    _constraintSolver = new btSequentialImpulseConstraintSolver();

    _softRigidDynamicsWorld = new btSoftRigidDynamicsWorld( _collisionDispatcher,
                                                           _broadphaseInterface,
                                                           _constraintSolver,
                                                           _collisionConfig );

    _softRigidDynamicsWorld->setGravity( btVector3( 0.0f, 0.0f, -9.8f ) );

}

void GFXPhysicWorld::addRigidBody( GFX3DMeshInfo *meshInfo, float mass )
{
    btCollisionShape *btcollisionshape = new btBoxShape( btVector3( meshInfo->dimension.x * 0.5f,
                                                                    meshInfo->dimension.y * 0.5f,
                                                                    meshInfo->dimension.z * 0.5f ) );
    btTransform bttransform;

    mat4 mat;

    vec4 rotx = { 1.0f, 0.0f, 0.0f, meshInfo->rotation.x },
         roty = { 0.0f, 1.0f, 0.0f, meshInfo->rotation.y },
         rotz = { 0.0f, 0.0f, 1.0f, meshInfo->rotation.z };

    console_print("1");

    mat4_identity( &mat );

    mat4_translate( &mat, &mat, &meshInfo->location );

    mat4_rotate( &mat, &mat, &rotz );

    mat4_rotate( &mat, &mat, &roty );

    mat4_rotate( &mat, &mat, &rotx );

    bttransform.setFromOpenGLMatrix( ( float * )&mat );

    console_print("2");

    btDefaultMotionState *btdefaultmotionstate = NULL;

    btdefaultmotionstate = new btDefaultMotionState( bttransform );


    btVector3 localinertia( 0.0f, 0.0f, 0.0f );

    console_print("3");

    if( mass ) btcollisionshape->calculateLocalInertia( mass, localinertia );


    meshInfo->btrigidbody = new btRigidBody( mass,
                                            btdefaultmotionstate,
                                            btcollisionshape,
                                            localinertia );

    meshInfo->btrigidbody->setUserPointer( meshInfo );

    console_print("4");

    _softRigidDynamicsWorld->addRigidBody( meshInfo->btrigidbody );
}

void GFXPhysicWorld::update()
{
    _softRigidDynamicsWorld->stepSimulation( 1.0f / 60.0f );
}

} /* namespace gfxe */
