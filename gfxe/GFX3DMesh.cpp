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

using namespace gfxe;

GFX3DMesh::GFX3DMesh( GFX3DModelInfo* pModelInfo, GFX3DMeshInfo* pMeshInfo, int meshIdx ) :
        m_pModelInfo( pModelInfo ), m_pMeshInfo( pMeshInfo ), m_nMeshIndex( meshIdx )
{
    console_print( pMeshInfo->name );
//    if( !strcmp( pMeshInfo->name, "momo" ) ) return;
//    if( !strcmp( pMeshInfo->name, "tree" ) ) return;
//    if( !strcmp( pMeshInfo->name, "leaf" ) ) return;
//    if( !strcmp( pMeshInfo->name, "backgroud" ) ) return;

    if( !strcmp( pMeshInfo->name, "balloon" )  ) {
        GFXPhysicWorld::Instance()->AddRigidBody( pMeshInfo, 1.0f );
        pMeshInfo->location.z = 40;
    } else {
        GFXPhysicWorld::Instance()->AddRigidBody( pMeshInfo, 0.0f );
    }

    if( pMeshInfo->objtrianglelist->objmaterial == NULL ) {
        console_print( "no material" );
        return;
    }
    if( pMeshInfo->objtrianglelist->objmaterial->dissolve == 1.0f ) {
        console_print( "solid" );
        GFXRenderManager::Instance()->AddRenderFunc( this, &GFX3DMesh::RenderSolid, RenderGroup_Solid );
    } else {
        console_print( "alpha" );
        GFXRenderManager::Instance()->AddRenderFunc( this, &GFX3DMesh::RenderAlpha, RenderGroup_Alpha );
    }
}

GFX3DMesh::~GFX3DMesh()
{
}

void GFX3DMesh::RenderSolid()
{
    GFX_push_matrix();

//    GFX_translate( m_pMeshInfo->location.x,
//            m_pMeshInfo->location.y,
//            m_pMeshInfo->location.z );

    mat4 mat;
    m_pMeshInfo->btrigidbody->getWorldTransform().getOpenGLMatrix( ( float * )&mat );
    console_print("%f,%f,%f", mat.m[3].x, mat.m[3].y, mat.m[3].z);
    GFX_multiply_matrix( &mat );

    OBJ_draw_mesh( m_pModelInfo, m_nMeshIndex );

    GFX_pop_matrix();
}

void GFX3DMesh::RenderAlpha()
{
    GFX_push_matrix();

//    GFX_translate( m_pMeshInfo->location.x,
//            m_pMeshInfo->location.y,
//            m_pMeshInfo->location.z );
    mat4 mat;
    m_pMeshInfo->btrigidbody->getWorldTransform().getOpenGLMatrix( ( float * )&mat );
    console_print("%f,%f,%f", mat.m[3].x, mat.m[3].y, mat.m[3].z);
    GFX_multiply_matrix( &mat );

    glCullFace( GL_FRONT );

    OBJ_draw_mesh( m_pModelInfo, m_nMeshIndex );

    glCullFace( GL_BACK );
    OBJ_draw_mesh( m_pModelInfo, m_nMeshIndex );

    GFX_pop_matrix();

}
