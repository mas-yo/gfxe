/*
 * GFXCamera.h
 *
 *  Created on: 2013/05/06
 *      Author: yoshi
 */

#ifndef __gfxe_GfxCamera__
#define __gfxe_GfxCamera__

#include "gfxe.h"
#include "Singleton.h"

namespace gfxe
{

enum CameraMode {
    CameraMode_Rotation,
    CameraMode_Target
};

class GFXCamera : public Singleton<GFXCamera>
{
private:
    int m_nCameraMode;
    vec3 m_v3Position;
    vec3 m_v3Rotation;
    vec3 m_v3Target;
    vec3 m_v3Up;

public:
    GFXCamera();
    virtual ~GFXCamera();

    void SetPosition( const vec3& pos );
    void SetRotation( const vec3& rot );
    void SetTarget( const vec3& tgt );
    void SetUp( const vec3& up );

    void MovePosition( float dx, float dy, float dz );
    void MoveRotation( float dx, float dy, float dz );
    void MoveTarget( float dx, float dy, float dz );

    const vec3& GetPosition() { return m_v3Position; }
    const vec3& GetTarget() { return m_v3Target; }
    const vec3& GetRotation() { return m_v3Rotation; }

    void Update();
};

} /* namespace gfxe */
#endif /* GFXCAMERA_H_ */
