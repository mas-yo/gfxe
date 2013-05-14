/*
 * GFXPhysicWorld.h
 *
 *  Created on: 2013/05/06
 *      Author: yoshi
 */

#ifndef __gfxe_GfxPhysicWorld__
#define __gfxe_GfxPhysicWorld__

#include "gfxe.h"
#include "Singleton.h"

namespace gfxe
{

class GFXPhysicWorld : public Singleton<GFXPhysicWorld>
{
private:
    btSoftBodyRigidBodyCollisionConfiguration *_collisionConfig = nullptr;
    btCollisionDispatcher *_collisionDispatcher = nullptr;
    btBroadphaseInterface *_broadphaseInterface = nullptr;
    btConstraintSolver *_constraintSolver = nullptr;
    btSoftRigidDynamicsWorld *_softRigidDynamicsWorld = nullptr;


public:
    GFXPhysicWorld();
    virtual ~GFXPhysicWorld();

    void initialize();
    void addRigidBody( GFX3DMeshInfo* meshInfo, float mass );
    void update();
};

} /* namespace gfxe */
#endif /* GFXPHYSICWORLD_H_ */
