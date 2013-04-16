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

GFX3DMesh::GFX3DMesh( OBJMESH* pMeshInfo ) : m_pMeshInfo( pMeshInfo ), m_unqShader()
{

}

GFX3DMesh::~GFX3DMesh()
{
    GFXRenderManager::Instance()->RemoveRenderable( this );
}

void GFX3DMesh::Create()
{
    GFXShaderSimple* pShader = new GFXShaderSimple();
    pShader->Create();
    m_unqShader.reset( pShader );
    create_vao(m_pMeshInfo, m_unqShader->GetProgram() );
    GFXRenderManager::Instance()->AddRenderable( this );
}

void GFX3DMesh::Render()
{
    glBindVertexArrayOES( m_pMeshInfo->vao );
//    PROGRAM_draw( m_unqShader->GetProgram());
    m_unqShader.get()->SetUniformVariable();

    for( int i = 0; i < m_pMeshInfo->n_objtrianglelist; ++i )
        glDrawElements(GL_TRIANGLES, m_pMeshInfo->objtrianglelist[i].n_indice_array, GL_UNSIGNED_SHORT, NULL);

}