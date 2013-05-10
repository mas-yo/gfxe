/*
 * GFXCamera.cpp
 *
 *  Created on: 2013/05/06
 *      Author: yoshi
 */

#include "GFXCamera.h"

namespace gfxe
{

GFXCamera::GFXCamera() :
        _cameraMode( CameraMode_Rotation ),
        _position( { 0.0f, 0.0f, 0.0f } ),
        _rotation( { 0.0f, 0.0f, 0.0f } ),
        _targetPosition( { 0.0f, 0.0f, 0.0f } ),
        _upPosition( { 0.0f, 0.0f, 0.0f } )
{
    // TODO Auto-generated constructor stub

}

GFXCamera::~GFXCamera()
{
    // TODO Auto-generated destructor stub
}

void GFXCamera::setPosition( const vec3& pos )
{
    _position = pos;
}

void GFXCamera::setRotation( const vec3& rot )
{
    _cameraMode = CameraMode_Rotation;
    _rotation = rot;
}

void GFXCamera::setTarget( const vec3& tgt )
{
    _cameraMode = CameraMode_Target;
    _targetPosition = tgt;
}

void GFXCamera::movePosition( float dx, float dy, float dz )
{
    _position.x += dx;
    _position.y += dy;
    _position.z += dz;
}

void GFXCamera::moveTarget( float dx, float dy, float dz )
{
    _cameraMode = CameraMode_Target;
    _targetPosition.x += dx;
    _targetPosition.y += dy;
    _targetPosition.z += dz;
}

void GFXCamera::moveRotation( float dx, float dy, float dz )
{
    _cameraMode = CameraMode_Rotation;
    _rotation.x += dx;
    _rotation.y += dy;
    _rotation.z += dz;
}

void GFXCamera::setUp( const vec3& up )
{
    _cameraMode = CameraMode_Target;
    _upPosition = up;
}

void GFXCamera::update()
{

    GFX_set_matrix_mode( MODELVIEW_MATRIX );
    GFX_load_identity();

    switch( _cameraMode ) {
    case CameraMode_Rotation:
        GFX_translate( _position.x, _position.y, _position.z );
        GFX_rotate( _rotation.x, 1.0f, 0.0f, 0.0f );
        GFX_rotate( _rotation.y, 0.0f, 1.0f, 0.0f );
        GFX_rotate( _rotation.z, 0.0f, 0.0f, 1.0f );
//
//    GFX_rotate( 90.0f, 1.0f, 0.0f, 0.0f );
        mat4_invert( GFX_get_modelview_matrix() );
        break;

    case CameraMode_Target:
        GFX_look_at( &_position, &_targetPosition, &_upPosition );
        break;
    }

}

} /* namespace gfxe */
