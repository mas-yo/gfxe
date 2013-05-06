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
    btSoftBodyRigidBodyCollisionConfiguration *m_pConfig = NULL;
    btCollisionDispatcher *m_pDispatcher = NULL;
    btBroadphaseInterface *m_pBroadphase = NULL;
    btConstraintSolver *m_pSolver = NULL;
    btSoftRigidDynamicsWorld *m_pDynamicsWorld = NULL;


public:
    GFXPhysicWorld();
    virtual ~GFXPhysicWorld();

    void Initialize();
    void AddRigidBody( GFX3DMeshInfo* meshInfo, float mass );
};

} /* namespace gfxe */
#endif /* GFXPHYSICWORLD_H_ */
