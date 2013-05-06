/*
 * GFXCamera.cpp
 *
 *  Created on: 2013/05/06
 *      Author: yoshi
 */

#include "C:/Users/yoshi/Documents/GitHub/gfxe/gfxe/GFXCamera.h"

namespace gfxe
{

GFXCamera::GFXCamera() :
        m_nCameraMode( CameraMode_Rotation ),
        m_v3Position( { 0.0f, 0.0f, 0.0f } ),
        m_v3Rotation( { 0.0f, 0.0f, 0.0f } ),
        m_v3Target( { 0.0f, 0.0f, 0.0f } ),
        m_v3Up( { 0.0f, 0.0f, 0.0f } )
{
    // TODO Auto-generated constructor stub

}

GFXCamera::~GFXCamera()
{
    // TODO Auto-generated destructor stub
}

void GFXCamera::SetPosition( const vec3& pos )
{
    m_v3Position = pos;
}

void GFXCamera::SetRotation( const vec3& rot )
{
    m_nCameraMode = CameraMode_Rotation;
    m_v3Rotation = rot;
}

void GFXCamera::SetTarget( const vec3& tgt )
{
    m_nCameraMode = CameraMode_Target;
    m_v3Target = tgt;
}

void GFXCamera::MovePosition( float dx, float dy, float dz )
{
    m_v3Position.x += dx;
    m_v3Position.y += dy;
    m_v3Position.z += dz;
}

void GFXCamera::MoveTarget( float dx, float dy, float dz )
{
    m_nCameraMode = CameraMode_Target;
    m_v3Target.x += dx;
    m_v3Target.y += dy;
    m_v3Target.z += dz;
}

void GFXCamera::MoveRotation( float dx, float dy, float dz )
{
    m_nCameraMode = CameraMode_Rotation;
    m_v3Rotation.x += dx;
    m_v3Rotation.y += dy;
    m_v3Rotation.z += dz;
}

void GFXCamera::SetUp( const vec3& up )
{
    m_nCameraMode = CameraMode_Target;
    m_v3Up = up;
}

void GFXCamera::Update()
{

    GFX_set_matrix_mode( MODELVIEW_MATRIX );
    GFX_load_identity();

    switch( m_nCameraMode ) {
    case CameraMode_Rotation:
        GFX_translate( m_v3Position.x, m_v3Position.y, m_v3Position.z );
        GFX_rotate( m_v3Rotation.x, 1.0f, 0.0f, 0.0f );
        GFX_rotate( m_v3Rotation.y, 0.0f, 1.0f, 0.0f );
        GFX_rotate( m_v3Rotation.z, 0.0f, 0.0f, 1.0f );
//
//    GFX_rotate( 90.0f, 1.0f, 0.0f, 0.0f );
        mat4_invert( GFX_get_modelview_matrix() );
        break;

    case CameraMode_Target:
        GFX_look_at( &m_v3Position, &m_v3Target, &m_v3Up );
        break;
    }

}

} /* namespace gfxe */
