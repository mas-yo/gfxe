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
    int _cameraMode;
    vec3 _position;
    vec3 _rotation;
    vec3 _targetPosition;
    vec3 _upPosition;

public:
    GFXCamera();
    virtual ~GFXCamera();

    void setPosition( const vec3& pos );
    void setRotation( const vec3& rot );
    void setTarget( const vec3& tgt );
    void setUp( const vec3& up );

    void movePosition( float dx, float dy, float dz );
    void moveRotation( float dx, float dy, float dz );
    void moveTarget( float dx, float dy, float dz );

    const vec3& getPosition() { return _position; }
    const vec3& getTarget() { return _targetPosition; }
    const vec3& getRotation() { return _rotation; }

    void update();
};

} /* namespace gfxe */
#endif /* GFXCAMERA_H_ */
