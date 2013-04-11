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

using namespace gfxe;

GFX3DMesh::GFX3DMesh( OBJMESH* pMeshInfo, GFXShaderProgram* pShader ) : m_pMeshInfo( pMeshInfo ), m_pShader( pShader )
{

}

GFX3DMesh::~GFX3DMesh()
{
}

void GFX3DMesh::Create()
{
    create_vao(m_pMeshInfo, m_pShader->GetProgram() );
    GFXRenderManager::Instance()->AddRenderable( this );
}

void GFX3DMesh::Render()
{
    glBindVertexArrayOES( m_pMeshInfo->vao );
    PROGRAM_draw( m_pShader->GetProgram()) ;

    for( int i = 0; i < m_pMeshInfo->n_objtrianglelist; ++i )
        glDrawElements(GL_TRIANGLES, m_pMeshInfo->objtrianglelist[i].n_indice_array, GL_UNSIGNED_SHORT, NULL);

}