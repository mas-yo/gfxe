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

using namespace gfxe;

GFX3DMesh::GFX3DMesh( GFX3DModelInfo* pModelInfo, GFX3DMeshInfo* pMeshInfo, int meshIdx ) :
        m_pModelInfo( pModelInfo ), m_pMeshInfo( pMeshInfo ), m_nMeshIndex( meshIdx )
{
    console_print( pMeshInfo->name );
//    if( !strcmp( pMeshInfo->name, "momo" ) ) return;
//    if( !strcmp( pMeshInfo->name, "tree" ) ) return;
//    if( !strcmp( pMeshInfo->name, "leaf" ) ) return;
//    if( !strcmp( pMeshInfo->name, "backgroud" ) ) return;

    if( pMeshInfo->objtrianglelist->objmaterial->dissolve == 1.0f ) {
        GFXRenderManager::Instance()->AddRenderFunc( this, &GFX3DMesh::RenderSolid, RenderGroup_Solid );
    } else {
        GFXRenderManager::Instance()->AddRenderFunc( this, &GFX3DMesh::RenderAlpha, RenderGroup_Alpha );
    }
}

GFX3DMesh::~GFX3DMesh()
{
}

void GFX3DMesh::RenderSolid()
{
    GFX_push_matrix();

    GFX_translate( m_pMeshInfo->location.x,
            m_pMeshInfo->location.y,
            m_pMeshInfo->location.z );

    OBJ_draw_mesh( m_pModelInfo, m_nMeshIndex );

    GFX_pop_matrix();
}

void GFX3DMesh::RenderAlpha()
{
    GFX_push_matrix();

    GFX_translate( m_pMeshInfo->location.x,
            m_pMeshInfo->location.y,
            m_pMeshInfo->location.z );

    glCullFace( GL_FRONT );

    OBJ_draw_mesh( m_pModelInfo, m_nMeshIndex );

    glCullFace( GL_BACK );
    OBJ_draw_mesh( m_pModelInfo, m_nMeshIndex );

    GFX_pop_matrix();

}
