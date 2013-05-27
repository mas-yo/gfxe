//
//  GFX3DMesh.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFX3DMesh.h"
#include "gfxe.h"
#include "glutil.h"
#include "GFXRenderManager.h"
#include "GFXShaderSimple.h"
#include "GFXPhysicWorld.h"
#include "TargetFunction.h"

using namespace gfxe;

GFX3DMesh::GFX3DMesh( GFX3DModelInfo* modelInfo, GFX3DMeshInfo* meshInfo, int meshIdx ) :
        _modelInfo( modelInfo ), _meshInfo( meshInfo ), _meshIndex( meshIdx )
{
    console_print( meshInfo->name );
//    if( !strcmp( pMeshInfo->name, "momo" ) ) return;
//    if( !strcmp( pMeshInfo->name, "tree" ) ) return;
//    if( !strcmp( pMeshInfo->name, "leaf" ) ) return;
//    if( !strcmp( pMeshInfo->name, "backgroud" ) ) return;

    if( !strcmp( meshInfo->name, "balloon" )  ) {
        GFXPhysicWorld::Instance()->addRigidBody( meshInfo, 1.0f );
        meshInfo->location.z = 40;
    } else {
        GFXPhysicWorld::Instance()->addRigidBody( meshInfo, 0.0f );
    }

    if( meshInfo->objtrianglelist->objmaterial == NULL ) {
        console_print( "no material" );
        return;
    }
    if( meshInfo->objtrianglelist->objmaterial->dissolve == 1.0f ) {
        console_print( "solid" );
        GFXRenderManager::Instance()->addFunc( this, std::bind( &GFX3DMesh::renderSolid, this ), RenderGroup_Solid );
    } else {
        console_print( "alpha" );
        GFXRenderManager::Instance()->addFunc( this, std::bind( &GFX3DMesh::renderSolid, this ), RenderGroup_Alpha );
    }
}

GFX3DMesh::~GFX3DMesh()
{
}

void GFX3DMesh::renderSolid()
{
    GFX_push_matrix();

//    GFX_translate( m_pMeshInfo->location.x,
//            m_pMeshInfo->location.y,
//            m_pMeshInfo->location.z );

    mat4 mat;
    _meshInfo->btrigidbody->getWorldTransform().getOpenGLMatrix( ( float * )&mat );
    GFX_multiply_matrix( &mat );

    OBJ_draw_mesh( _modelInfo, _meshIndex );

    GFX_pop_matrix();
}

void GFX3DMesh::renderAlpha()
{
    GFX_push_matrix();

//    GFX_translate( m_pMeshInfo->location.x,
//            m_pMeshInfo->location.y,
//            m_pMeshInfo->location.z );
    mat4 mat;
    _meshInfo->btrigidbody->getWorldTransform().getOpenGLMatrix( ( float * )&mat );
    GFX_multiply_matrix( &mat );

    glCullFace( GL_FRONT );

    OBJ_draw_mesh( _modelInfo, _meshIndex );

    glCullFace( GL_BACK );
    OBJ_draw_mesh( _modelInfo, _meshIndex );

    GFX_pop_matrix();

}
