/*
 * GFXPhysicWorld.cpp
 *
 *  Created on: 2013/05/06
 *      Author: yoshi
 */

#include "GFXPhysicWorld.h"

namespace gfxe
{

GFXPhysicWorld::GFXPhysicWorld() :
        m_pConfig(NULL),
        m_pDispatcher(NULL),
        m_pBroadphase(NULL),
        m_pSolver(NULL),
        m_pDynamicsWorld(NULL)
{
    // TODO Auto-generated constructor stub

}

GFXPhysicWorld::~GFXPhysicWorld()
{
    if( m_pDynamicsWorld ) {
        while( m_pDynamicsWorld->getNumCollisionObjects() )
        {
            btCollisionObject *btcollisionobject = m_pDynamicsWorld->getCollisionObjectArray()[ 0 ];
            btRigidBody *btrigidbody = btRigidBody::upcast( btcollisionobject );

            if( btrigidbody )
            {
                delete btrigidbody->getCollisionShape();
                delete btrigidbody->getMotionState();

                m_pDynamicsWorld->removeRigidBody( btrigidbody );
                m_pDynamicsWorld->removeCollisionObject( btcollisionobject );

                delete btrigidbody;
            }
        }

        delete m_pConfig;
        delete m_pDispatcher;
        delete m_pBroadphase;
        delete m_pSolver;
        delete m_pDynamicsWorld;
    }
}

void GFXPhysicWorld::Initialize()
{
    m_pConfig = new btSoftBodyRigidBodyCollisionConfiguration();

    m_pDispatcher = new btCollisionDispatcher( m_pConfig );

    m_pBroadphase = new btDbvtBroadphase();

    m_pSolver = new btSequentialImpulseConstraintSolver();

    m_pDynamicsWorld = new btSoftRigidDynamicsWorld( m_pDispatcher,
                                                  m_pBroadphase,
                                                  m_pSolver,
                                                  m_pConfig );

    m_pDynamicsWorld->setGravity( btVector3( 0.0f, 0.0f, -9.8f ) );

}

void GFXPhysicWorld::AddRigidBody( GFX3DMeshInfo *meshInfo, float mass )
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

    m_pDynamicsWorld->addRigidBody( meshInfo->btrigidbody );
}


} /* namespace gfxe */
